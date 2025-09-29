/*
=====================================================================================================================================================================================
Name: 12.c
Author: Preet Chandrakar
Description: Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.
Date: September 17, 2025
======================================================================================================================================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
	pid_t child_pid = fork();

	if (child_pid < 0)
	{
		perror("Error: Fork failed");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		// child process
		pid_t parent_pid = getppid(); // get parent's process id
		pid_t current_pid = getpid(); // get child's process id

		printf("Child process ID: = %d, Parent process ID: = %d", current_pid, parent_pid);

		sleep(2); // pauses the execution to let the parent run for a bit

		printf("\nSending SIGKILL signal from child process to parent process %d\n", parent_pid);
		kill(parent_pid, SIGKILL);

		sleep(1); // wait for parent again to run

		printf("Child's new parent process ID : %d\n", getppid());

		for (int i = 0; i <= 4; i++)
		{
			printf("Child process is working...\n", i);
			sleep(1);
		}
	}
	else
	{
		pid_t parent_pid = getpid();
		printf("Parent Process ID: = %d, Child process ID: = %d\n", parent_pid, child_pid);

		while (1)
		{
			printf("Parent process is working... PID = %d\n", parent_pid);
			sleep(1);
		}
	}
	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Parent Process ID: = 7567, Child process ID: = 7568
Parent process is working... PID = 7567
Parent process is working... PID = 7567
Child process ID: = 7568, Parent process ID: = 7567
Sending SIGKILL signal from child process to parent process 7567
Killed
iiitb@Preet:~/MyLinux/Hands_on_2$ Child's new parent process ID : 2031
Child process is working...
Child process is working...
Child process is working...
Child process is working...
Child process is working...
^C
*/
