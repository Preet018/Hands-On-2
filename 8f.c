/*
============================================================================================
 * Name: 8f.c
 * Author: Preet Chandrakar
 * Description: Write a separate program using signal system call to catch the following signals.
                f. SIGVTALRM (use setitimer system call)
 * Date: 12 Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void handler(int sig)
{
    printf("SIGVTALRM received!\n");
}

int main()
{
    struct itimerval timer;
    signal(SIGVTALRM, handler);

    timer.it_value.tv_sec = 2; // first firing after 2s CPU
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1; // repeats every 1s CPU
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    // Busy loop to consume CPU
    while (1)
    {
        for (volatile long i = 0; i < 1000000; i++)
            ;
    }

    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./8f
SIGVTALRM received!
SIGVTALRM received!
SIGVTALRM received!
SIGVTALRM received!
SIGVTALRM received!
SIGVTALRM received!
^C
*/