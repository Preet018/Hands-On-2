/*
============================================================================================
 * Name: 8e.c
 * Author: Preet Chandrakar
 * Description: Write a separate program using signal system call to catch the following signals.
                e. SIGALRM (use setitimer system call)
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
    printf("SIGALRM received (using setitimer ITIMER_REAL)\n");
}

int main()
{
    struct itimerval timer;
    signal(SIGALRM, handler);

    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    printf("Setting ITIMER_REAL for 3 seconds...\n");
    setitimer(ITIMER_REAL, &timer, NULL);

    while (1)
        pause();
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./8e
Setting ITIMER_REAL for 3 seconds...
SIGALRM received (using setitimer ITIMER_REAL)
*/