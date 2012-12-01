#include <stdio.h>
#include<stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <errno.h>

inline bool is_digit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}
bool name_is_all_digit(const char *name)
{
	int i;

	for (i = 0; name[i]; i ++) {
		if (! is_digit(name[i])) {
			return false;
		}
	}
	return true;
}

void super_killer(char **cmd, int size)
{
	int i;
	FILE *fp;
	DIR *ptdir;
	char path[4096], buffer[1024];
	struct dirent *ptdirent;

	ptdir = opendir("/proc");
	if (ptdir == NULL) {
		perror("opendir failed.");
		exit(-1);
	}

	while((ptdirent = readdir(ptdir)) != NULL) {
		if (ptdirent->d_type == DT_DIR) {
			if (name_is_all_digit(ptdirent->d_name)) {
				snprintf(path, sizeof(path), 
						 "/proc/%s/cmdline", 
						 ptdirent->d_name);
				if (access(path, F_OK) == 0) {
					fp = fopen(path, "r");
					if (fp == NULL) {
						printf("Open %s failed.\n", path);
						continue;
					}
					fgets(buffer, sizeof(buffer), fp);
					for (i = 0; i < size; i ++) {
						if (! strcmp(buffer, cmd[i])) {
							if (kill(atoi(
								ptdirent->d_name), 
									9) == -1) {
							printf("%s kill failed,%s.\n",
								   ptdirent->d_name,
								   strerror(errno));
								continue;
							}
							printf("%s was killed.\n", 
							   ptdirent->d_name);
						}
					}
				}
			}
		}
	}
	closedir(ptdir);
}

int main(int argc, char *argv[])
{
	super_killer(&argv[1], argc - 1);
	return 0;
}

