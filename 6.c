/*
=====================================================================================================================================================================================

Name: 6.c
Author: Preet Chandrakar
Description:Write a simple program to create three threads.

Date: September 17, 2025

======================================================================================================================================================================================

 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // For sleep()

void *thread_func(void *arg)
{
    int thread_id = *(int *)arg;
    printf("Thread %d is working\n", thread_id);
    sleep(1);
    printf("Thread %d completed.\n", thread_id);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[3]; // Array to store thread IDs
    int thread_args[3];

    // Create three threads
    for (int i = 0; i < 3; i++)
    {
        thread_args[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_func, (void *)&thread_args[i]) != 0)
        {
            fprintf(stderr, "Thread creation failed %d\n", i + 1);
            return 1;
        }
        printf("Main: Created thread successfully %d.\n", i + 1);
    }

    // Waiting for thread to coomplete
    for (int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
        printf("Main: Joined with thread %d.\n", i + 1);
    }

    printf("Main: All threads completed.\n");
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Main: Created thread successfully 1.
Thread 1 is working
Main: Created thread successfully 2.
Thread 2 is working
Main: Created thread successfully 3.
Thread 3 is working
Thread 1 completed.
Thread 2 completed.
Thread 3 completed.
Main: Joined with thread 1.
Main: Joined with thread 2.
Main: Joined with thread 3.
Main: All threads completed.
*/
