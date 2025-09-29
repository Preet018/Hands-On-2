/*
============================================================================
Name : 24.c
Author : Preet Chandrakar
Description : Write a program to create a message queue and print the key and message queue id.
Date: 21th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t key;
    int msgid;

    key = ftok(".", 'A');
    if (key == -1)
    {
        perror("ftok failed");
        exit(1);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget failed");
        exit(1);
    }

    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Message Queue Key: 1090855096
Message Queue ID: 0
*/