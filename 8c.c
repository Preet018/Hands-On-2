/*
============================================================================================
 * Name: 8c.c
 * Author: Preet Chandrakar
 * Description: Write a separate program using signal system call to catch the following signals.
                 c. SIGFPE
 * Date: 12 Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig)
{
    printf("SIGFPE received (Floating Point Exception).\n");
    exit(EXIT_FAILURE);
}

int main()
{
    signal(SIGFPE, handler);
    printf("Attempting to induce SIGFPE...\n");
    int zero = 0;
    int result = 10 / zero; // Division by zero
    (void)result;
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./8c
Attempting to induce SIGFPE...
SIGFPE received (Floating Point Exception).
*/