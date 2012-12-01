#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

//--------------------------------------------------------------------
// Macro definition
//--------------------------------------------------------------------
#define BUFFER_SIZE	1024

//--------------------------------------------------------------------
// Type definition
//--------------------------------------------------------------------
typedef struct
{
  char *data;
  int size;
  int payload_length;
} buf_t;

typedef struct
{
  buf_t *rbuf;
  buf_t *sbuf;
} conn_t;

//--------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------
conn_t **global_conn_list = NULL;
int global_conn_list_count = 0;

fd_set global_read_set, global_write_set, global_exception_set;
int global_maxfd = 0;

volatile sig_atomic_t global_exit_flag = 0;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
void net_register_read(int fd);
void net_unregister_read(int fd);
void net_register_write(int fd);
void net_unregister_write(int fd);
void net_register_exception(int fd);
void net_unregister_exception(int fd);

int net_accept(int listenfd);
int net_read(int fd);
int net_write(int fd);

int init_conn_list(int n);
void destroy_conn_list(void);

void dump_conn_list(void);

conn_t *create_conn_object(void);
void destroy_conn_object(conn_t * object);
void dump_conn_object(conn_t * object);

buf_t *create_buf_object(void);
void destroy_buf_object(buf_t * object);
void dump_buf_object(buf_t * object);

void *utils_safe_malloc(size_t size);
void utils_safe_free(void *ptr);

void sigpipe_handler(int signum);
void sigterm_handler(int signum);

void do_extra_job(void);
void parse_data(int fd);

//--------------------------------------------------------------------
// Main function
//--------------------------------------------------------------------
int main(int argc, char **argv)
{
  int listening_socket;
  unsigned short port;
  int backlog;

  //------------------------------------------------------------------
  // Initialize
  //------------------------------------------------------------------
  if (init_conn_list(1024) < 0)
  {
    exit(1);
  }

  FD_ZERO(&global_read_set);
  FD_ZERO(&global_write_set);
  FD_ZERO(&global_exception_set);

  global_maxfd = 0;

  //------------------------------------------------------------------
  // Parse command line arguments
  //------------------------------------------------------------------
  port = (unsigned short) strtol(argv[2], NULL, 10);
  backlog = (int) strtol(argv[3], NULL, 10);

  //------------------------------------------------------------------
  // step 1, create socket
  //------------------------------------------------------------------
  //int socket(int domain, int type, int protocol);
  if ((listening_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "Create listening_socket failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "listening_socket = %d.\n", listening_socket);

  //------------------------------------------------------------------
  // step 1.5, set SO_REUSEADDR & SO_REUSEPORT options
  //------------------------------------------------------------------
  int optval;

  optval = 1;
  //int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

#ifdef SO_REUSEPORT
  optval = 1;
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
#endif

  //------------------------------------------------------------------
  // step 2, bind
  //------------------------------------------------------------------
  struct sockaddr_in local_ipv4_address;

  memset(&local_ipv4_address, 0, sizeof(local_ipv4_address));
  //bzero(&local_ipv4_address);

  local_ipv4_address.sin_family = AF_INET;	// IPv4
  local_ipv4_address.sin_port = htons(port);	// NBO
  inet_pton(AF_INET, argv[1], &local_ipv4_address.sin_addr);

  //int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
  if (bind(listening_socket, (struct sockaddr *) &local_ipv4_address, sizeof(local_ipv4_address)) < 0)
  {
    fprintf(stderr, "Bind to %s:%d failed: %s\n", argv[1], port, strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "Bound to %s:%d successfully.\n", argv[1], port);

  //------------------------------------------------------------------
  // step 3, listen
  //------------------------------------------------------------------
  //int listen(int sockfd, int backlog);
  if (listen(listening_socket, backlog) < 0)
  {
    fprintf(stderr, "Listen on %s:%d failed: %s\n", argv[1], port, strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "Listen on %s:%d successfully.\n", argv[1], port);

  int n;
  fd_set rset, wset, eset;
  struct timeval to;

#if 0
  void FD_CLR(int fd, fd_set * set);
  int FD_ISSET(int fd, fd_set * set);
  void FD_SET(int fd, fd_set * set);
  void FD_ZERO(fd_set * set);
#endif

  net_register_read(listening_socket);

  //------------------------------------------------------------------
  // Set signal handlers
  //------------------------------------------------------------------
  struct sigaction act, oact;

#if 0
  struct sigaction
  {
    void (*sa_handler) (int);
    void (*sa_sigaction) (int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer) (void);
  };
#endif

  memset(&act, 0, sizeof(act));

  act.sa_handler = sigpipe_handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  sigaction(SIGPIPE, &act, &oact);

  memset(&act, 0, sizeof(act));

  act.sa_handler = sigterm_handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  sigaction(SIGINT, &act, &oact);
  sigaction(SIGQUIT, &act, &oact);
  sigaction(SIGTERM, &act, &oact);

  //------------------------------------------------------------------
  // Main loop
  //------------------------------------------------------------------
  for (;;)
  {
    if (global_exit_flag > 0)
    {
      fprintf(stdout, "It's time to exit, bye!\n");
      break;
    }

    dump_conn_list();

    rset = global_read_set;
    wset = global_write_set;
    eset = global_exception_set;

    to.tv_sec = 1;
    to.tv_usec = 0;

    // step 4, select
    //int select(int global_maxfd, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval *timeout);
    if ((n = select(global_maxfd + 1, &rset, &wset, &eset, &to)) < 0)
    {
      // failed
      if (errno == EINTR)
      {
	continue;
      }

      // FIXME: Check other error code.
      fprintf(stderr, "select() failed: %s\n", strerror(errno));
      break;
    }
    else if (n == 0)
    {
      // timeout
      fprintf(stdout, "timeout ...\n");
      do_extra_job();
    }
    else
    {
      // ready
      int i;

      for (i = 0; i <= global_maxfd; i++)
      {
	//int FD_ISSET(int fd, fd_set * set);
	if (FD_ISSET(i, &rset))
	{
	  if (i == listening_socket)
	  {
	    // accept new connection, add to global_read_set, global_write_set, global_exception_set
	    net_accept(i);
	  }
	  else
	  {
	    // read data
	    //fprintf(stdout, "TODO: read data on connection %d.\n", i);
	    net_read(i);
	    parse_data(i);
	  }
	}

	if (FD_ISSET(i, &wset))
	{
	  // send data
	  //fprintf(stdout, "TODO: write data on connection %d.\n", i);
	  net_write(i);
	}

#if 0
	if (FD_ISSET(i, &eset))
	{
	  // exception handling
	}
#endif
      }
    }
  }

  // TODO: shutdown(fd, SHUT_RD), close read end
  // TODO: Send all unsent data on every sockets
  // TODO: set SO_LINGER option on every sockets
  // TODO: close all sockets

  //------------------------------------------------------------------
  // final, close listening_socket
  //------------------------------------------------------------------
  close(listening_socket);

  destroy_conn_list();

  return 0;
}

void net_register_read(int fd)
{
  FD_SET(fd, &global_read_set);

  if (global_maxfd < fd)
  {
    global_maxfd = fd;
  }
}

void net_unregister_read(int fd)
{
  FD_CLR(fd, &global_read_set);
}

void net_register_write(int fd)
{
  FD_SET(fd, &global_write_set);

  if (global_maxfd < fd)
  {
    global_maxfd = fd;
  }
}

void net_unregister_write(int fd)
{
  FD_CLR(fd, &global_write_set);
}

void net_register_exception(int fd)
{
  FD_SET(fd, &global_exception_set);

  if (global_maxfd < fd)
  {
    global_maxfd = fd;
  }
}

void net_unregister_exception(int fd)
{
  FD_CLR(fd, &global_exception_set);
}

int net_accept(int listenfd)
{
  int new_connected_socket;
  struct sockaddr_in peer_ipv4_address;
  socklen_t peer_ipv4_address_length;
  char peer_ipv4_address_string[] = "ddd.ddd.ddd.ddd";

  peer_ipv4_address_length = sizeof(peer_ipv4_address);

  //int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
  if ((new_connected_socket = accept(listenfd, (struct sockaddr *) &peer_ipv4_address, &peer_ipv4_address_length)) < 0)
  {
    // failed
    fprintf(stderr, "Accept new connection on %d failed: %s\n", listenfd, strerror(errno));
    return -1;
  }
  else
  {
    inet_ntop(AF_INET, &peer_ipv4_address.sin_addr, peer_ipv4_address_string, sizeof(peer_ipv4_address_string));

    fprintf(stdout, "Accepted a new connection(%d) from %s:%d.\n", new_connected_socket, peer_ipv4_address_string, ntohs(peer_ipv4_address.sin_port));

    conn_t *newconn;

    newconn = create_conn_object();

    if (!newconn)
    {
      // TODO: Response error message to client.
      close(new_connected_socket);
      return -2;
    }
    else
    {
      // attach newconn to global_conn_list
      global_conn_list[new_connected_socket] = newconn;

      net_register_read(new_connected_socket);
      //net_register_write(new_connected_socket);
      //net_register_exception(new_connected_socket);
    }
  }

  return 0;
}

int net_read(int fd)
{
  conn_t *conn = global_conn_list[fd];

  if (!conn)
  {
    fprintf(stderr, "Fatal error: conn_t object not exists\n");
    return -1;
  }

  buf_t *rbuf = conn->rbuf;

  if (!rbuf)
  {
    fprintf(stderr, "Fatal error: buf_t object not exists\n");
    return -2;
  }

  if (!rbuf->data)
  {
    fprintf(stderr, "Fatal error: buf_t->data object not exists\n");
    return -3;
  }

  ssize_t n;

read_again:
  //ssize_t read(int fd, void *buf, size_t count);
  if ((n = read(fd, rbuf->data + rbuf->payload_length, rbuf->size - rbuf->payload_length)) < 0)
  {
    if (errno == EINTR)
    {
      goto read_again;
    }

    fprintf(stderr, "Receive data on socket %d failed: %s\n", fd, strerror(errno));
    return -4;
  }
  else if (n == 0)
  {
    // Connection closed by peer.
    close(fd);

    destroy_conn_object(conn);
    global_conn_list[fd] = NULL;

    net_unregister_read(fd);
    net_unregister_write(fd);
    net_unregister_exception(fd);
  }
  else
  {
    fprintf(stdout, "Received %d bytes on socket %d.\n", n, fd);
    rbuf->payload_length += n;

    if (rbuf->payload_length >= rbuf->size)
    {
      // buffer is full
      int newsize = rbuf->size * 2;
      char *newdata = utils_safe_malloc(newsize);

      if (!newdata)
      {
	fprintf(stderr, "Allocate more memory for connection %d failed.\n", fd);
	// FIXME: How to do?
      }
      else
      {
	memcpy(newdata, rbuf->data, rbuf->payload_length);
	utils_safe_free(rbuf->data);
	rbuf->data = newdata;
	rbuf->size = newsize;
      }
    }
  }

  return 0;
}

int net_write(int fd)
{
  conn_t *conn = global_conn_list[fd];

  if (!conn)
  {
    fprintf(stderr, "Fatal error: conn_t object not exists\n");
    return -1;
  }

  buf_t *sbuf = conn->sbuf;

  if (!sbuf)
  {
    fprintf(stderr, "Fatal error: buf_t object not exists\n");
    return -2;
  }

  if (!sbuf->data)
  {
    fprintf(stderr, "Fatal error: buf_t->data object not exists\n");
    return -3;
  }

  ssize_t n;

write_again:
  //ssize_t write(int fd, const void *buf, size_t count);
  if ((n = write(fd, sbuf->data, sbuf->payload_length)) < 0)
  {
    // failed
    if (errno == EINTR)
    {
      goto write_again;
    }
    else if (errno == EPIPE)
    {
      // Connection closed by peer.
      close(fd);

      destroy_conn_object(conn);
      global_conn_list[fd] = NULL;

      net_unregister_read(fd);
      net_unregister_write(fd);
      net_unregister_exception(fd);
    }

    // FIXME: Check other error code!
    fprintf(stderr, "Send data on socket %d failed: %s\n", fd, strerror(errno));
    return -4;
  }
  else
  {
    fprintf(stdout, "Sent %d bytes on socket %d successfully.\n", n, fd);

    //void *memmove(void *dest, const void *src, size_t n);
    memmove(sbuf->data, sbuf->data + n, sbuf->payload_length - n);
    sbuf->payload_length -= n;

    if (sbuf->payload_length <= 0)
    {
      net_unregister_write(fd);
    }
  }

  return 0;
}

//--------------------------------------------------------------------
// global_conn_list related function
//--------------------------------------------------------------------
int init_conn_list(int n)
{
  global_conn_list = utils_safe_malloc(n * sizeof(conn_t *));

  if (!global_conn_list)
  {
    fprintf(stderr, "Allocate memory for global_conn_list failed.\n");
    return -1;
  }

  int i;

  for (i = 0; i < n; i++)
  {
    global_conn_list[i] = NULL;
  }

  global_conn_list_count = n;

  return 0;
}

void destroy_conn_list(void)
{
  int i;

  for (i = 0; i < global_conn_list_count; i++)
  {
    if (global_conn_list[i])
    {
      destroy_conn_object(global_conn_list[i]);
      global_conn_list[i] = NULL;
    }
  }

  utils_safe_free(global_conn_list);
  global_conn_list = NULL;
  global_conn_list_count = 0;
}

void dump_conn_list(void)
{
  int i;

  for (i = 0; i < global_conn_list_count; i++)
  {
    if (global_conn_list[i])
    {
      fprintf(stdout, "Connection: %d\n", i);
      dump_conn_object(global_conn_list[i]);
    }
  }
}

//--------------------------------------------------------------------
// conn_t object related functions
//--------------------------------------------------------------------
conn_t *create_conn_object(void)
{
  conn_t *ptr;

  ptr = utils_safe_malloc(sizeof(conn_t));

  if (!ptr)
  {
    fprintf(stderr, "Allocate memory for conn_t failed.\n");
    return NULL;
  }

  ptr->rbuf = create_buf_object();
  ptr->sbuf = create_buf_object();

  if (!ptr->rbuf || !ptr->sbuf)
  {
    destroy_buf_object(ptr->rbuf);
    destroy_buf_object(ptr->sbuf);

    utils_safe_free(ptr);

    return NULL;
  }

  return ptr;
}

void destroy_conn_object(conn_t * object)
{
  if (!object)
  {
    fprintf(stderr, "Non-exists conn_t object.\n");
    return;
  }

  destroy_buf_object(object->rbuf);
  destroy_buf_object(object->sbuf);

  utils_safe_free(object);

  //object = NULL;
}

void dump_conn_object(conn_t * object)
{
  if (!object)
  {
    fprintf(stderr, "Non-exists conn_t object.\n");
    return;
  }

  fprintf(stdout, "\tconn: %p\n", object);

  dump_buf_object(object->rbuf);
  dump_buf_object(object->sbuf);
}

//--------------------------------------------------------------------
// buf_t object related functions
//--------------------------------------------------------------------
buf_t *create_buf_object(void)
{
  buf_t *ptr;

  ptr = utils_safe_malloc(sizeof(buf_t));

  if (!ptr)
  {
    fprintf(stderr, "Allocate memory for buf_t object failed.\n");
    return NULL;
  }

  ptr->data = utils_safe_malloc(BUFFER_SIZE);

  if (!ptr->data)
  {
    utils_safe_free(ptr);
    fprintf(stderr, "Allocate memory for buf_t object failed.\n");
    return NULL;
  }

  ptr->size = BUFFER_SIZE;
  ptr->payload_length = 0;

  return ptr;
}

void destroy_buf_object(buf_t * object)
{
  if (!object)
  {
    fprintf(stderr, "Non-exists buf_t object.\n");
    return;
  }

  utils_safe_free(object->data);
  utils_safe_free(object);

  //object = NULL;
}

void dump_buf_object(buf_t * object)
{
  if (!object)
  {
    fprintf(stderr, "Non-exists buf_t object.\n");
    return;
  }

  fprintf(stdout, "\t\tbuf: %p\n", object);
  fprintf(stdout, "\t\t\tbuf->data = %p\n", object->data);
  fprintf(stdout, "\t\t\tbuf->size = %d\n", object->size);
  fprintf(stdout, "\t\t\tbuf->payload_length = %d\n", object->payload_length);
}

//--------------------------------------------------------------------
// Utilities
//--------------------------------------------------------------------
void *utils_safe_malloc(size_t size)
{
  void *ptr;

  ptr = malloc(size);

  if (!ptr)
  {
    fprintf(stderr, "Allocate memory failed, required size = %d.\n", size);
    // FIXME: retry some times.
    return NULL;
  }

  return ptr;
}

void utils_safe_free(void *ptr)
{
  if (ptr)
  {
    free(ptr);
  }
#ifdef _DEBUG_
  else
  {
    fprintf(stderr, "Attempt to free NULL pointer.\n");
  }
#endif
}

//--------------------------------------------------------------------
// Signal handlers
//--------------------------------------------------------------------
void sigpipe_handler(int signum)
{
  fprintf(stdout, "Caught signal %d.\n", signum);
}

void sigterm_handler(int signum)
{
  fprintf(stdout, "Caught signal %d.\n", signum);
  global_exit_flag++;
}

//--------------------------------------------------------------------
// Extra job
//--------------------------------------------------------------------
void do_extra_job(void)
{
  fprintf(stdout, "Do extra job here.\n");
}

void parse_data(int fd)
{
  fprintf(stdout, "TODO: parse data on socket %d.\n", fd);
}

ssize_t buffered_write(int fd, const void *buf, size_t count)
{
  conn_t *conn = global_conn_list[fd];

  if (!conn)
  {
    fprintf(stderr, "Fatal error: conn_t object not exists\n");
    return -1;
  }

  buf_t *sbuf = conn->sbuf;

  if (!sbuf)
  {
    fprintf(stderr, "Fatal error: buf_t object not exists\n");
    return -2;
  }

  if (!sbuf->data)
  {
    fprintf(stderr, "Fatal error: buf_t->data object not exists\n");
    return -3;
  }

  if (sbuf->size - sbuf->payload_length < count)
  {
    int newsize = sbuf->payload_length + count;
    char *newdata = utils_safe_malloc(newsize);

    if (!newdata)
    {
      // FIXME: How to do?
      fprintf(stderr, "Allocate more memory for sbuf object failed.\n");
      return -1;
    }
    else
    {
      memcpy(newdata, sbuf->data, sbuf->payload_length);
      utils_safe_free(sbuf->data);
      sbuf->data = newdata;
      sbuf->size = newsize;
    }
  }

  memcpy(sbuf->data + sbuf->payload_length, buf, count);
  sbuf->payload_length += count;

  if (sbuf->payload_length > 0)
  {
    net_register_write(fd);
  }

  return 0;
}


/*
 *alt+1. /test 0.0.0.0 8000 10
 *alt+2. nc 192.168.207.81 8000
 */



