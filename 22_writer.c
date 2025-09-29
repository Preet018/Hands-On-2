/*
============================================================================
Name : 22_writer.c
Author : Preet Chandrakar
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 21th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "22_myfifo"

int main()
{
    int fd;
    char *msg = "Hello from program who's writting in FIFO within 10 seconds!\n";

    fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0)
    {
        mkfifo(FIFO_NAME, 0666);
    }

    write(fd, msg, strlen(msg));
    close(fd);

    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
*/
