/*
============================================================================================
 * Name: 11.c
 * Author: Preet Chandrakar
 * Description: Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - use sigaction system call.
 * Date: 17 Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    struct sigaction sa;

    // Ignore SIGINT
    sa.sa_handler = SIG_IGN;  // ignore signal
    sigemptyset(&sa.sa_mask); // no additional signals blocked
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT disabled temporarily. Press Ctrl+C, program will continue.\n");
    sleep(5); // demonstrate ignoring

    // Restore default action
    sa.sa_handler = SIG_DFL; // default action
    sigaction(SIGINT, &sa, NULL);

    printf("Default SIGINT action restored.\n");

    while (1)
    {
        printf("Running.... press Ctrl+C to terminate\n");
        sleep(2);
    }

    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./11
SIGINT disabled temporarily. Press Ctrl+C, program will continue.
^C
Default SIGINT action restored.
Running.... press Ctrl+C to terminate
Running.... press Ctrl+C to terminate
Running.... press Ctrl+C to terminate
^C
 */
