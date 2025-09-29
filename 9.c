/*
=====================================================================================================================================================================================
Name: 9.c
Author: Preet Chandrakar
Description: Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - Use signal system call.

Date: September 17, 2025
======================================================================================================================================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	printf("SIGINT disabled temporarily. pressing ctrl+c keeps program running.\n");

	signal(SIGINT, SIG_IGN);

	sleep(5); // sleep for few seconds to demonsrate ignoring

	printf("Default SIGINT action restored.\n");
	signal(SIGINT, SIG_DFL);

	// infinite running of program until SIGNIT terminates it
	while (1)
	{
		printf("Running.... press ctrl+c to terminate \n");
		sleep(2);
	}
	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
SIGINT disabled temporarily. pressing ctrl+c keeps program running.
Default SIGINT action restored.
Running.... press ctrl+c to terminate
Running.... press ctrl+c to terminate
Running.... press ctrl+c to terminate
*/
