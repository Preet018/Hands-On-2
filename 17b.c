/*
============================================================================================
 * Name: 17b.c
 * Author: Preet Chandrakar
 * Description: Write a program to execute ls -l | wc.
        b. use dup2
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
        dup2(fd[1], 1);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        exit(1);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(1);
    }
}
/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
     83     740    4111
*/
