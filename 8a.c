/*
============================================================================================
 * Name: 8a.c
 * Author: Preet Chandrakar
 * Description: Write a separate program using signal system call to catch the following signals.
                a. SIGSEGV
 * Date: 12 Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig)
{
    printf("SIGSEGV received: segmentation fault error.\n");
    exit(EXIT_FAILURE);
}

int main()
{
    signal(SIGSEGV, handler);
    printf("Attempting to induce SIGSEGV...\n");
    int *ptr = NULL;
    *ptr = 10; // Dereferencing NULL pointer
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./8a
Attempting to induce SIGSEGV...
SIGSEGV received: segmentation fault error.
*/