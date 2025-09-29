/*
============================================================================
Name : 20_reader.c
Author : Preet Chandrakar
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 21th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "20_myfifo"
#define BUF_SIZE 100

int main()
{
    int fd;
    char buf[BUF_SIZE];

    fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }

    int n = read(fd, buf, sizeof(buf));
    if (n > 0)
    {
        buf[n] = '\0';
        printf("Reader program has read:\n%s", buf);
    }

    close(fd);
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./b.out
Reader program has read:
Hello from program who's writting in FIFO!
*/
