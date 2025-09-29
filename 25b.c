/*
============================================================================
Name : 25b.c
Author : Preet Chandrakar
Description : Write a program to create a message queue and print the key and message queue id.
                b. uid, gid
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

    printf("Owner UID: %u\n", ds.msg_perm.uid);
    printf("Owner GID: %u\n", ds.msg_perm.gid);
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out 1
Owner UID: 1000
Owner GID: 1000
*/