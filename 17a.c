/*
============================================================================================
 * Name: 17a.c
 * Author: Preet Chandrakar
 * Description: Write a program to execute ls -l | wc.
        a. use dup
 * Date: 21st Sept, 2025
=============================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd[2];
    pid_t pid;

    pipe(fd);

    pid = fork();

    if (pid == 0)
    {
        close(fd[0]);
        close(1);
        dup(fd[1]);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        exit(1);
    }
    else
    {
        close(fd[1]);
        close(0);
        dup(fd[0]);
        close(fd[0]);
        execlp("wc", "wc", NULL);
        exit(1);
    }
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
     83     740    4111
*/
