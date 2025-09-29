/*
============================================================================
Name : 30d.c
Author : Preet Chandrakar
Description : Write a program to create a shared memory.
                d. Remove the shared memory
Date: 21th Sep, 2025.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    key_t key = 5678;
    int shmid;

    // Get the shared memory segment
    shmid = shmget(key, 1024, 0666);

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        printf("Delete UnSuccessfully");
    }
    else
    {
        printf("Delete Successfully");
    }
    return 0;
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


iiitb@Preet:~/MyLinux/Hands_on_2$ ./30d
Delete Successfullyiiitb@Preet:~/MyLinux/Hands_on_2$ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status
0x00000000 4          iiitb      600        524288     2          dest
0x00000000 12         iiitb      600        524288     2          dest

*/
