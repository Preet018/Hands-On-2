/*
============================================================================
Name : 25a.c
Author : Preet Chandrakar
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                a. access permission
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

    printf("Access permission (octal): %#o\n", ds.msg_perm.mode & 0777);
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ipcmk -Q
Message queue id: 1
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out 1
Access permission (octal): 0644
*/