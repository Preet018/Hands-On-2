/*
============================================================================
Name : 28.c
Author : Preet Chandrakar
Description : Write a program to change the exiting message queue permission. (Use msqid_ds structure)
Date: 21th Sep, 2025.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main()
{
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, IPC_CREAT | 0666);
    struct msqid_ds st_to_set;
    struct msqid_ds st_to_read;

    msgctl(msqid, IPC_STAT, &st_to_read);
    printf("Current access Permissions - %o\n", st_to_read.msg_perm.mode);

    st_to_set.msg_perm.mode = 0777;
    msgctl(msqid, IPC_SET, &st_to_set);
    msgctl(msqid, IPC_STAT, &st_to_read);
    printf("New access Permissions - %o\n", st_to_read.msg_perm.mode);
    return (0);
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Current access Permissions - 666
New access Permissions - 666
iiitb@Preet:~/MyLinux/Hands_on_2$ sudo ./a.out
[sudo] password for iiitb:
Current access Permissions - 666
New access Permissions - 777
*/
