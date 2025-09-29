/*
============================================================================================
 * Name: 13a.c
 * Author: Preet Chandrakar
 * Description: Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.
 * Date: 21st Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sign)
{
	printf("Caught signal %d\n", sign);
}

int main()
{
	printf("PID of this process: %d\n", getpid());

	// Handler for SIGSTOP
	signal(SIGSTOP, handler);

	// Waiting for signals
	while (1)
	{
		printf("Waiting for signal>>>\n");
		sleep(2);
	}

	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./13a
PID of this process: 10178
Waiting for signal>>>
Waiting for signal>>>
Waiting for signal>>>
Waiting for signal>>>

[1]+  Stopped                 ./13a
*/
