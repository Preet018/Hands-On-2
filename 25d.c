/*
============================================================================
Name : 25d.c
Author : Preet Chandrakar
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                d. time of last change in the message queue
Date: 21th Sept, 2025.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
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

    printf("Last change: %s", ctime(&ds.msg_ctime));
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out 1
Last change: Sun Sep 21 21:53:48 2025
*/