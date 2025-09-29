/*
============================================================================
Name : 27a.c
Author : Preet Chandrakar
Description : Write a program to receive messages from the message queue.
                a. with 0 as a flag
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

    msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);
    printf("Received (blocking): %s\n", msg.msg_text);

    return 0;
}

/*
Terminal 1:
iiitb@Preet:~/MyLinux/Hands_on_2$ ./27_sender
Enter message:

Terminal 2:
./a.out

Terminal 1:
This is test content for problem 27a.

Terminal 2:
Received (blocking): This is test content for problem 27a.

Terminal 1:
Message sent successfully.
*/