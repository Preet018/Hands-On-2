/*
============================================================================
Name : 30b.c
Author : Preet Chandrakar
Description : Write a program to create a shared memory.
                attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
Date: 21th Sep, 2025.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
  key_t key = 5678;
  int shmid;
  char *shm_ptr;

  shmid = shmget(key, 1024, 0666);
  shm_ptr = shmat(shmid, NULL, SHM_RDONLY);
  printf("Attached shared memory with read-only permission.\n");
  printf("Data from shared memory: %s\n", shm_ptr);

  printf("Attempting to write to read-only shared memory...\n");
  strcpy(shm_ptr, "Attempting to overwrite"); // Uncommenting this will cause a segmentation fault
  printf("Write operation was blocked. This message should not be visible if the write attempt was made.\n");

  // Detach the shared memory
  shmdt(shm_ptr);

  return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./30b
Attached shared memory with read-only permission.
Segmentation fault (core dumped)
*/
