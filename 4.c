/*
=====================================================================================================================================================================================
Name: 4.c
Author: Preet Chandrakar
Description: Write a program to measure how much time is taken to execute 100 getppid ( ) system call. Use time stamp counter.
Date: September 11, 2025
======================================================================================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <x86intrin.h> //for rdtsc(): read time stamp couter
#include <fcntl.h>

int main()
{
	unsigned long long start_cycle, end_cycle;
	pid_t ppid;

	unsigned int aux; // serialize to avoid out of order executio

	// start timestamp
	start_cycle = __rdtsc();

	for (int i = 0; i < 100; i++)
	{
		getppid();
	}

	// end timestamp
	end_cycle = __rdtsc();

	unsigned long long Total_cycle = end_cycle - start_cycle;
	printf("Total time required to Execute 100 getppid() calls: %llu\n", Total_cycle);

	printf("Average cycle required for every getppid() call: %llu\n", Total_cycle / 100);
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Total time required to Execute 100 getppid() calls: 167431
Average cycle required for every getppid() call: 1674
*/
