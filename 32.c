/*
============================================================================
Name : 32.c
Author : Preet Chandrakar
Description: Demonstration of semaphore usage for protecting resources
             a. Protect critical section using binary semaphore
             b. Rewrite ticket number creation with shared memory + semaphore
             c. Use counting semaphore for handling multiple pseudo-resources
             d. Cleanup created IPC resources
Date: 24th Sept, 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Perform "P" (wait/down) operation
void acquire_sem(int sid)
{
    struct sembuf op = {0, -1, 0};
    if (semop(sid, &op, 1) == -1)
    {
        perror("semop P");
        exit(EXIT_FAILURE);
    }
}

// Perform "V" (signal/up) operation
void release_sem(int sid)
{
    struct sembuf op = {0, 1, 0};
    if (semop(sid, &op, 1) == -1)
    {
        perror("semop V");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    key_t sem_key, shm_key, count_key;
    int bin_sem, cnt_sem, shm_id;
    int *ticket_no;
    union semun uarg;

    // a. Create binary semaphore
    sem_key = ftok("/tmp", 'B');
    if (sem_key == -1)
    {
        perror("ftok bin");
        exit(EXIT_FAILURE);
    }

    bin_sem = semget(sem_key, 1, IPC_CREAT | 0666);
    if (bin_sem == -1)
    {
        perror("semget bin");
        exit(EXIT_FAILURE);
    }

    uarg.val = 1;
    if (semctl(bin_sem, 0, SETVAL, uarg) == -1)
    {
        perror("semctl bin");
        exit(EXIT_FAILURE);
    }
    printf("Binary semaphore initialized.\n");

    // b. Create shared memory for ticket counter
    shm_key = ftok("/tmp", 'T');
    if (shm_key == -1)
    {
        perror("ftok shm");
        exit(EXIT_FAILURE);
    }

    shm_id = shmget(shm_key, sizeof(int), IPC_CREAT | 0666);
    if (shm_id == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    ticket_no = (int *)shmat(shm_id, NULL, 0);
    if (ticket_no == (void *)-1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    *ticket_no = 0;

    // Multiple processes increment ticket safely
    for (int i = 0; i < 5; i++)
    {
        pid_t cpid = fork();
        if (cpid == 0)
        {
            acquire_sem(bin_sem);

            int temp = *ticket_no;
            usleep(120000); // simulate delay
            temp++;
            *ticket_no = temp;

            printf("[Child %d] Ticket number updated to %d\n", i + 1, temp);

            release_sem(bin_sem);
            shmdt(ticket_no);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < 5; i++)
        wait(NULL);

    printf("Final ticket value after all children: %d\n", *ticket_no);

    // c. Counting semaphore with 2 slots
    count_key = ftok("/tmp", 'R');
    if (count_key == -1)
    {
        perror("ftok count");
        exit(EXIT_FAILURE);
    }

    cnt_sem = semget(count_key, 1, IPC_CREAT | 0666);
    if (cnt_sem == -1)
    {
        perror("semget count");
        exit(EXIT_FAILURE);
    }

    uarg.val = 2;
    if (semctl(cnt_sem, 0, SETVAL, uarg) == -1)
    {
        perror("semctl count");
        exit(EXIT_FAILURE);
    }

    printf("Counting semaphore created (2 pseudo resources).\n");

    acquire_sem(cnt_sem);
    printf("First resource acquired.\n");
    acquire_sem(cnt_sem);
    printf("Second resource acquired.\n");

    release_sem(cnt_sem);
    release_sem(cnt_sem);
    printf("Released both resources.\n");

    // d. Cleanup resources
    if (semctl(bin_sem, 0, IPC_RMID) == -1)
        perror("semctl remove bin");
    if (semctl(cnt_sem, 0, IPC_RMID) == -1)
        perror("semctl remove count");

    shmdt(ticket_no);
    if (shmctl(shm_id, IPC_RMID, NULL) == -1)
        perror("shmctl remove");

    printf("All semaphores and shared memory removed.\n");

    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Binary semaphore initialized.
[Child 1] Ticket number updated to 1
[Child 2] Ticket number updated to 2
[Child 3] Ticket number updated to 3
[Child 4] Ticket number updated to 4
[Child 5] Ticket number updated to 5
Final ticket value after all children: 5
Counting semaphore created (2 pseudo resources).
First resource acquired.
Second resource acquired.
Released both resources.
All semaphores and shared memory removed.
*/