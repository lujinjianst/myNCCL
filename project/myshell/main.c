#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int get_command(char *command, char **para)
{
	write(STDOUT_FILENO, "Panda$ ", 7);
	int i = 0;
	int j = 0;
	char *p = NULL;

	fgets(command, 1023, stdin);
	command[strlen(command)-1] = '\0';
	if(strcmp(command, "exit") == 0)
	{
		exit(0);
	}

	for(j = 0; command[j] != '\0'; j++)
	{
		if(command[j] == '|')
		{
			break;
		}
	}

	if(command[j] == '\0')
	{
		p = strtok(command, " ");
		while(p != NULL)
		{
			para[i] = p;
			i++;
			p = strtok(NULL, " ");
		}
		para[i] = NULL;

		return 1;
	}
	else
	{
		command[j] = '\0';
		p = strtok(command, " ");
		while(p != NULL)
		{
			para[i] = p;
			i++;
			p = strtok(NULL, " ");
		}
		para[i] = NULL;
		i++;
		p = strtok(&command[j]+1, " ");
		while(p != NULL)
		{
			para[i] = p;
			i++;
			p = strtok(NULL, " ");
		}
		para[i] = NULL;		
		return 2;
	}

	return 0;
}

void deal_command_one(char **para)
{
	pid_t pid = fork();

	if(pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if(pid == 0)
	{
		execvp(para[0], para);
		perror("execl");
		exit(1);
	}
	wait(NULL);
	return;
}

void deal_command_pipe(char **para)
{
	int i = 0;
	while(para[i] != NULL)
	{
		i++;
	}
	i++;

	int fd[2];
	if(pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}

	pid_t pid1 = fork();
	if(pid1 < 0)
	{
		perror("fork1");
		exit(1);
	}
	else if(pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execvp(para[0], para);
		perror("exec");
		exit(1);
	}
	pid_t pid2 = fork();
	if(pid2 < 0)
	{
		perror("fork2");
		exit(1);
	}
	else if(pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execvp(para[i], para+i);
		perror("exec2");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);

	wait(NULL);
	wait(NULL);


}
int main(void)
{
	char command[1024];
	char *para[128];

	int para_type;

	while(1)
	{
		para_type = get_command(command, para);

		switch(para_type)
		{
			case 1 : deal_command_one(para);break;
			case 2 : deal_command_pipe(para);break;
			default : break;
		}
	}		

	return 0;
}
