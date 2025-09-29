/*
============================================================================
Name : 30a.c
Author : Preet Chandrakar
Description : Write a program to create a shared memory.
                a. Write some data to the shared memory
Date: 21th Sep, 2025.
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

    char *data = shmat(shmid, (void *)0, 0);
    printf("Enter text to put in shared memory: ");
    scanf("%[^\n]s", data);

    printf("Write successful\n");
    return (0);
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./30a
Enter text to put in shared memory: This is test content for problem 30a.
Write successful

iiitb@Preet:~/MyLinux/Hands_on_2$ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status
0x00000000 4          iiitb      600        524288     2          dest
0x00000000 12         iiitb      600        524288     2          dest
0x0000162e 26         iiitb      666        1024       0

*/