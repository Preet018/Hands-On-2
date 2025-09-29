/*
=====================================================================================================================================================================================
Name: 1a.c
Author: Preet Chandrakar
Description: Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
				a. ITIMER_REAL
Date: September 11, 2025
======================================================================================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h> //working with real time operation

void handler(int signum) // signum passing numeric value to handler (incase of SIGALRM 14)
{
	printf(" ITIMER_REAL: Time expired for SIGALRM \n");
}

int main()
{
	struct itimerval Realtime;

	signal(SIGALRM, handler);

	// setting timer for first 10 sec and 10 microsec
	Realtime.it_value.tv_sec = 10;
	Realtime.it_value.tv_usec = 10;

	// then repeat after every 10 sec and 10 microsec
	Realtime.it_interval.tv_sec = 10;
	Realtime.it_interval.tv_usec = 10;

	// setting the start timer
	setitimer(ITIMER_REAL, &Realtime, NULL);

	printf("waiting for the ITIMER_REAL....\n");

	while (1)
		pause();

	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
waiting for the ITIMER_REAL....
ITIMER_REAL: Time expired for SIGALRM

//"After every 10 sec it will print the same line again
*/
