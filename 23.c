/*
============================================================================
Name : 23.c
Author : Preet Chandrakar
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date: 21th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>

int main()
{
    long max_files = sysconf(_SC_OPEN_MAX);
    printf("Maximum files a process can open: %ld\n", max_files);

    int fds_pipe[2];
    pipe(fds_pipe);

    int flags = fcntl(fds_pipe[1], F_GETFL);
    fcntl(fds_pipe[1], F_SETFL, flags | O_NONBLOCK);

    char buf = 'A';
    int count = 0;
    while (write(fds_pipe[1], &buf, 1) == 1)
    {
        count++;
    }

    printf("Pipe size (circular buffer) measured: %d bytes\n", count);

    close(fds_pipe[0]);
    close(fds_pipe[1]);

    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Maximum files a process can open: 1024
Pipe size (circular buffer) measured: 65536 bytes
*/