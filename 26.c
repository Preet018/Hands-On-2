/*
============================================================================
Name : 26.c
Author : Preet Chandrakar
Description : Write a program to send messages to the message queue. Check $ipcs -q
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

    key = ftok("26_file.txt", 65);
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

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

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Enter message: Hello!! Fragy this side.
Message sent successfully.
iiitb@Preet:~/MyLinux/Hands_on_2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x135d7515 1          iiitb      644        0            0
0x41050258 2          iiitb      666        26           1
*/