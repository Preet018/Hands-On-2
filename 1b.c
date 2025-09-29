/*
=====================================================================================================================================================================================
Name: 1b.c
Author: Preet Chandrakar
Description: Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
                b. ITIMER_VIRTUAL
Date: September 11, 2025
======================================================================================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h> //working with real time operation

void handler(int signum) // signum passing numeric value to handler (incase of SIGVTALRM 26)
{
        printf(" ITIMER_VIRTUAL: Time expired for SIGVTALRM \n");
}

int main()
{
        struct itimerval Virtualtime;

        signal(SIGVTALRM, handler); // install handler for SIGVTALRM

        // setting timer for first 10 sec + 10 microsec
        Virtualtime.it_value.tv_sec = 10;
        Virtualtime.it_value.tv_usec = 10;

        // then repeat after every 10 sec + 10 microsec
        Virtualtime.it_interval.tv_sec = 10;
        Virtualtime.it_interval.tv_usec = 10;

        // setting the start timer
        setitimer(ITIMER_VIRTUAL, &Virtualtime, NULL);

        printf(" Waiting for ITIMER_VIRTUAL....\n");

        // the loop is running because ITIMER_VIRTUAL only decrements when the process is running in user space (on CPU)
        while (1)
        {
                for (volatile int i = 0; i < 1000000; i++)
                        ;
        }
        return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Waiting for ITIMER_VIRTUAL....
ITIMER_VIRTUAL: Time expired for SIGVTALRM

//After every 10 sec it will print the same line again
*/
