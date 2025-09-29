/*
============================================================================
Name : 29.c
Author : Preet Chandrakar
Description : Write a program to remove the message queue.
Date: 21th Sep, 2025.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

// Remove a message queue.
int main()
{
    key_t key = ftok("/home/iiitb/MyLinux/Hands_on_2/my_unique_file28", 'a');
    int msqid = msgget(key, 0);

    (msgctl(msqid, IPC_RMID, NULL) == -1) ? printf("Delete unsuccessful\n") : printf("Delete successful\n");

    return (0);
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./29
Delete unsuccessful
*/
