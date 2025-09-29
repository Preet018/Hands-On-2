/*
============================================================================
Name : 27_sender.c
Author : Preet Chandrakar
Description : Write a program to receive messages from the message queue.
                a. with 0 as a flag
                b. with IPC_NOWAIT as a flag
Date: 21th Sept, 2025.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_TEXT 512

struct msg_buffer
{
    long msg_type;
    char msg_text[MAX_TEXT];
};

int main()
{
    key_t key;
    int msgid;
    struct msg_buffer msg;

    key = ftok("27_file.txt", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    printf("Enter message: ");
    fgets(msg.msg_text, MAX_TEXT, stdin);
    msg.msg_type = 1;

    if (msgsnd(msgid, &msg, strlen(msg.msg_text) + 1, 0) == -1)
    {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent successfully.\n");
    return 0;
}