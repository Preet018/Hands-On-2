/*
============================================================================
Name : 30c.c
Author : Preet Chandrakar
Description : Write a program to create a shared memory.
                c. Detach the shared memory
Date: 21th Sep, 2024.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{
    key_t key = 5678;
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);

    char *data = shmat(shmid, NULL, 0);
    printf("Detaching\n");
    shmdt(data);

    return (0);
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./30c
Detaching
*/
