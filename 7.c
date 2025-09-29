/*
=======================================================================================================================================================================================
Name: 7.c
Author: Preet Chandrakar
Description: Write a simple program to print the created thread ids.

Date: September 17, 2025

=======================================================================================================================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread_func(void *arg)
{
	pthread_t thread_id = pthread_self();
	printf("Thread %s has ID: %lu\n", (char *)arg, thread_id);
	pthread_exit(NULL);
}

int main()
{
	pthread_t T1, T2, T3;

	pthread_create(&T1, NULL, thread_func, "Thread-1");
	pthread_create(&T2, NULL, thread_func, "Thread-2");
	pthread_create(&T3, NULL, thread_func, "Thread-3");

	pthread_join(T1, NULL);
	pthread_join(T2, NULL);
	pthread_join(T3, NULL);
	printf("All thread completed");

	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Thread Thread-1 has ID: 129108413511360
Thread Thread-3 has ID: 129108396725952
Thread Thread-2 has ID: 129108405118656
*/
