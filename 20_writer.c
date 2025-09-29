/*
============================================================================
Name : 20_writer.c
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
#include <string.h>

#define FIFO_NAME "20_myfifo"

int main()
{
    int fd;
    char *msg = "Hello from program who's writting in FIFO!\n";

    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        perror("mkfifo");
    }

    fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }

    write(fd, msg, strlen(msg));
    close(fd);

    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
*/
