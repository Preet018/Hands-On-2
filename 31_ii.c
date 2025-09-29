/*
============================================================================
Name : 31_ii.c
Author : Preet Chandrakar
Description : Write a program to create a semaphore and initialize value to the semaphore.
                ii. Create a counting semaphore
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
    key_t key = ftok(".", 'C');
    semid = semget(key, 2, IPC_CREAT | 0666);
    arg.val = 5;
    semctl(semid, 0, SETVAL, arg);
    printf("Counting Semaphore created with ID: %d and initialized to 5.\n", semid);

    arg.val = 3; // Initialize the second semaphore to 3
    semctl(semid, 0, SETVAL, arg);
    printf("Counting Semaphore created with ID: %d and initialized to 3.\n", semid);
    return 0;
}
/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Counting Semaphore created with ID: 1 and initialized to 5.
Counting Semaphore created with ID: 1 and initialized to 3.
*/
