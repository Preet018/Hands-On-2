/*
============================================================================================
 * Name: 15.c
 * Author: Preet Chandrakar
 * Description: Write a simple program to send some data from parent to the child process.
 * Date: 21st Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	int fd[2]; // fd[0] = read end, fd[1] = write end
	pid_t pid;
	char msgw[] = "Msg to the child process from parent process.";
	char msgr[100];

	// creating pipe
	pipe(fd);

	// creating fork
	pid = fork();

	if (pid < 0)
	{
		printf("Fork creation failed");
		exit(1);
	}

	if (pid > 0)
	{
		close(fd[0]);
		write(fd[1], msgw, strlen(msgw) + 1);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		read(fd[0], msgr, sizeof(msgr));
		printf("Child received: %s\n", msgr);
		close(fd[0]);
	}

	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./15
Child received: Msg to the child process from parent process.
*/
