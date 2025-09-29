/*
============================================================================================
 * Name: 8g.c
 * Author: Preet Chandrakar
 * Description: Write a separate program using signal system call to catch the following signals.
                g. SIGPROF (use setitimer system call)
 * Date: 12 Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig)
{
    printf("SIGPROF received (Profiling Timer Alarm)\n");
}

int main()
{
    struct itimerval timer;
    signal(SIGPROF, handler);

    timer.it_value.tv_sec = 7;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    printf("Setting ITIMER_PROF for 7 seconds...\n");
    setitimer(ITIMER_PROF, &timer, NULL);

    // Busy loop to consume CPU
    while (1)
    {
        for (volatile long i = 0; i < 1000000; i++)
            ;
    }
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./8g
Setting ITIMER_PROF for 7 seconds...
SIGPROF received (Profiling Timer Alarm)
^C
*/