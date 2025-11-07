/*
============================================================================
Name : 25c.c
Author : Preet Chandrakar
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                c. time of last message sent and received
Date: 21th Sept, 2025.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static void showtime(const char *label, time_t t)
{
    if (t == 0)
        printf("%s: never\n", label);
    else
        printf("%s: %s", label, ctime(&t));
}

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

    showtime("Last sent", ds.msg_stime);
    showtime("Last received", ds.msg_rtime);
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out 1
Last sent: never
Last received: never
*/