/*
============================================================================================
 * Name: 8d.c
 * Author: Preet Chandrakar
 * Description: Write a separate program using signal system call to catch the following signals.
                d. SIGALRM (use alarm system call)
 * Date: 12 Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("SIGALRM received (using alarm())\n");
}

int main()
{
    signal(SIGALRM, handler);
    printf("Setting alarm for 2 seconds...\n");
    alarm(2);
    while (1)
        pause();
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./8d
Setting alarm for 2 seconds...
SIGALRM received (using alarm())
*/