/*
============================================================================================
 * Name: 14.c
 * Author: Preet Chandrakar
 * Description: Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
 * Date: 21st Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd[2]; // fd[0]: read end, fd[1]: write end
	char msgw[] = "Message from pipe: Hello Linux.";
	char msgr[100];

	// Creating pipe
	pipe(fd);

	printf("File Descriptor of read end: %d\nFile Descriptor of write end: %d\n", fd[0], fd[1]);

	// Writing into the pipe
	write(fd[1], msgw, strlen(msgw) + 1);

	// Reading from the pipe
	read(fd[0], msgr, sizeof(msgr));

	// Displaying message on the monitor
	printf("Reading msg from pipe...\n%s", msgr);

	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./14
File Descriptor of read end: 3
File Descriptor of write end: 4
Reading msg from pipe...
Message from pipe: Hello Linux.
*/
