/*
============================================================================
Name : 31_i.c
Author : Preet Chandrakar
Description : Write a program to create a semaphore and initialize value to the semaphore.
                i. Create a binary semaphore
Date: 21th Sep, 2025.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main()
{
    union semun arg;
    int semid;
    key_t key = ftok(".", 'B');
    semid = semget(key, 1, IPC_CREAT | 0666);
    semctl(semid, 0, SETVAL, arg);
    printf("Binary Semaphore created with ID: %d and initialized to 1.\n", semid);

    return 0;
}
/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Binary Semaphore created with ID: 0 and initialized to 1.
*/
