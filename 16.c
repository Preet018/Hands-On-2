/*
============================================================================================
 * Name: 16.c
 * Author: Preet Chandrakar
 * Description: Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
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
	int fd1[2], fd2[2]; // fd1 for Parent to Child, fd2 for Child to Parent
	pid_t pid;
	char msgp[] = "Msg to the Child from Parent!";
	char msgc[] = "Msg to the Parent from Child!";
	char buffer[100];

	// Creating two pipes
	pipe(fd1);
	pipe(fd2);

	// Forking process
	pid = fork();

	if (pid > 0)
	{
		close(fd1[0]);
		close(fd2[1]);

		// Writing message to child
		write(fd1[1], msgp, strlen(msgp) + 1);
		close(fd1[1]);

		// Reading message from child
		read(fd2[0], buffer, sizeof(buffer));
		printf("Parent received: %s\n", buffer);
		close(fd2[0]);
	}
	else
	{
		close(fd1[1]);
		close(fd2[0]);

		// Reading message from parent
		read(fd1[0], buffer, sizeof(buffer));
		printf("Child received: %s\n", buffer);
		close(fd1[0]);

		// Sending message to parent
		write(fd2[1], msgc, strlen(msgc) + 1);
		close(fd2[1]);
	}

	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Child received: Msg to the Child from Parent!
Parent received: Msg to the Parent from Child!
*/
