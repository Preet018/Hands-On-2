/*
============================================================================
Name : 22_reader.c
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
#include <sys/select.h>

#define FIFO_NAME "22_myfifo"
#define BUF_SIZE 100

int main()
{
    int fd;
    char buf[BUF_SIZE];

    fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK);
    if (fd < 0)
    {
        mkfifo(FIFO_NAME, 0666);
        fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK);
    }

    fd_set readfds;
    struct timeval timeout;

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Reader waiting up to 10 seconds for data.\n");
    fflush(stdout);

    int ret = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1)
    {
        perror("select");
        close(fd);
        exit(1);
    }
    else if (ret == 0)
    {
        printf("Timeout: No data written to FIFO within 10 seconds.\n");
    }
    else
    {
        if (FD_ISSET(fd, &readfds))
        {
            int n = read(fd, buf, sizeof(buf) - 1);
            if (n > 0)
            {
                buf[n] = '\0';
                printf("Reader program has read:\n%s", buf);
            }
            else
            {
                printf("No data could be read (error).\n");
            }
        }
    }

    close(fd);
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./b.out
Reader waiting up to 10 seconds for data.
Reader program has read:
Hello from program who's writting in FIFO within 10 seconds!
*/