/*
============================================================================
Name : 21_p1.c
Author : Preet Chandrakar
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 21th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "21_myfifo"
#define BUF_SIZE 100

int main()
{
    int fd;
    char *msg = "Hello from program-1 who's writing in FIFO!\n";
    char buf[BUF_SIZE];

    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        perror("mkfifo");
        exit(1);
    }

    fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0)
    {
        perror("open for write");
        exit(1);
    }

    write(fd, msg, strlen(msg));
    close(fd);

    fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0)
    {
        perror("open for read");
        exit(1);
    }

    int n = read(fd, buf, BUF_SIZE);
    if (n > 0)
    {
        buf[n] = '\0';
        printf("Program-1 has read:\n%s", buf);
    }
    close(fd);

    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Program-1 has read:
Hello from program-2 who's writing in FIFO!
*/