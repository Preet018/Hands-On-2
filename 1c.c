/*
=====================================================================================================================================================================================
Name: 1c.c
Author: Preet Chandrakar
Description: Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
                a. ITIMER_PROF
Date: September 11, 2025
======================================================================================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h> //working with real time operation

void handler(int signum) // signum passing numeric value to handler (incase of SIGALRM 27)
{
        printf(" ITIMER_PROF: Time expired for SIGPROF \n");
}

int main()
{
        struct itimerval Proftime; // profiling timer measures both user CPU time and system CPU time

        signal(SIGPROF, handler);

        // setting timer for first 10 sec and 10 microsec
        Proftime.it_value.tv_sec = 10;
        Proftime.it_value.tv_usec = 10;

        // then repeat after every 10 sec and 10 microsec
        Proftime.it_interval.tv_sec = 10;
        Proftime.it_interval.tv_usec = 10;

        // setting the start timer
        setitimer(ITIMER_PROF, &Proftime, NULL);

        printf("waiting for the ITIMER_PROF....\n");

        // Running the loop to keep CPU and kernel busy
        while (1)
        {
                for (volatile int i = 1; i < 1000000; i++)
                        ;
                write(STDOUT_FILENO, " ", 0);
        }

        return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
waiting for the ITIMER_PROF....
ITIMER_PROF: Time expired for SIGPROF

//it will print the same line again after every 10 sec

*/
