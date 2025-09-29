/*
======================================================================================================================================================================================
Name: 10.c
Author: Preet Chandrakar
Description:Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE

Date:September 17, 2025
======================================================================================================================================================================================

 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int sig_num)
{
	if (sig_num == SIGSEGV)
	{
		printf("\nreceived SIGSEGV: Segmentation fault error\n");
		exit(EXIT_FAILURE);
	}
	else if (sig_num == SIGINT)
	{
		printf("\nreceived SIGINT: ctrl+c terminates the program \n");
		exit(EXIT_SUCCESS);
	}

	else if (sig_num == SIGFPE)
	{
		printf("\nreceived SIGFPE:(floating point execption");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Caught unexpected signal %d\n", sig_num);
	}
}

int main()
{
	struct sigaction sa;

	// Initialization
	sa.sa_handler = signal_handler; // set the signal handler function
	sigemptyset(&sa.sa_mask);		// clear the signal mask
	sa.sa_flags = 0;

	if (sigaction(SIGSEGV, &sa, NULL) == -1)
	{
		perror("Failed setting SIGSEGV handler");
		return EXIT_FAILURE;
	}

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Failed setting SIGINT handler");
		return EXIT_FAILURE;
	}

	if (sigaction(SIGFPE, &sa, NULL) == -1)
	{
		perror("Failed setting SIGFPE handler");
		return EXIT_FAILURE;
	}

	printf("successfully signal handler registered. Try to generate signals\n");
	printf("press ctrl+c to trigger SIGINT\n");
	printf("Division by zero to trigger SIGFPE\n");
	printf("Inavlid memory access to trigger SIGSEGV\n");

	while (1)
	{
		pause();
	}
	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
successfully signal handler registered. Try to generate signals
press ctrl+c to trigger SIGINT
Division by zero to trigger SIGFPE
Inavlid memory access to trigger SIGSEGV
^C
received SIGINT: ctrl+c terminates the program
*/
