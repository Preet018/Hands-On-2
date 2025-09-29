/*
============================================================================================
 * Name: 8b.c
 * Author: Preet Chandrakar
 * Description: Write a separate program using signal system call to catch the following signals.
                b. SIGINT
 * Date: 12 Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("SIGINT received (Ctrl+C). Exiting program successfully.\n");
    exit(EXIT_SUCCESS);
}

int main()
{
    signal(SIGINT, handler);
    printf("Program running. Press Ctrl+C to trigger SIGINT...\n");
    while (1)
        pause(); // Wait for signal
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./8b
Program running. Press Ctrl+C to trigger SIGINT...
^CSIGINT received (Ctrl+C). Exiting program successfully.
*/