/*
============================================================================
Name : 25h.c
Author : Preet Chandrakar
Description : Write a program to create a message queue and print the key and message queue id.
                h. pid of the msgsnd and msgrcv
Date: 21th Sept, 2025.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <msqid>\n", argv[0]);
        exit(1);
    }

    int msqid = atoi(argv[1]);
    struct msqid_ds ds;

    if (msgctl(msqid, IPC_STAT, &ds) == -1)
    {
        perror("msgctl");
        exit(1);
    }

    printf("Last msgsnd PID: %d\n", ds.msg_lspid);
    printf("Last msgrcv PID: %d\n", ds.msg_lrpid);
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out 1
Last msgsnd PID: 0
Last msgrcv PID: 0
*/