/*
============================================================================================
 * Name: 18.c
 * Author: Preet Chandrakar
 * Description: Write a program to find out total number of directories on the pwd. execute ls -l | grep ^d | wc ? Use only dup2.
 * Date: 21st Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd1[2], fd2[2];
	pid_t pid1, pid2;
	pipe(fd1);

	// Implemennting for First child: ls -l
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd1[0]);
		dup2(fd1[1], 1);
		close(fd1[1]);
		execlp("ls", "ls", "-l", NULL);
		exit(1);
	}

	pipe(fd2);

	// Implementing Second child: grep ^d
	pid2 = fork();

	if (pid2 == 0)
	{
		close(fd1[1]);
		dup2(fd1[0], 0);
		close(fd1[0]);
		close(fd2[0]);
		dup2(fd2[1], 1);
		close(fd2[1]);

		execlp("grep", "grep", "^d", NULL);
		exit(1);
	}

	// Implementing 'wc' from Parent
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[1]);
	dup2(fd2[0], 0);
	close(fd2[0]);

	execlp("wc", "wc", NULL);
	exit(1);
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
	  0       0       0
*/
