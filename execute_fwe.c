#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * execute_fwe - creates a new process and excutes
 * input command
 * @argv: array of arguments in string format
 *
 * Return: on success (0)
 */

void execute_fwe(char *argv[])
{
	pid_t child_pid;
	pid_t ppid;
	int status;
	unsigned int i;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error-fork:");
		exit(1);
	}
	if (child_pid == 0)
	{
		ppid = getppid();
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error-exec:");
			exit(2);
		}
	}
	else
	{
		wait(&status);
	}
}

