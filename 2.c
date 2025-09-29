/*
=====================================================================================================================================================================================
Name: 2.c
Author: Preet Chandrakar
Description: Write a program to print the system resource limits. Use getrlimit system call.
Date: September 11, 2025
======================================================================================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

void resource_limit(const char *res_name, int resource)
{
	struct rlimit limit;

	if (getrlimit(resource, &limit) == -1)
	{
		perror("Failed to fetch the resource");
		return;
	}
	printf("%s Soft limit value= ", res_name);
	if (limit.rlim_cur == RLIM_INFINITY)
		printf("Unlimited");
	else
		printf("%llu", (unsigned long long)limit.rlim_cur);

	printf("\nHard limit value= ");
	if (limit.rlim_max == RLIM_INFINITY)
		printf("Unlimited");

	else
		printf("%llu", (unsigned long long)limit.rlim_max);
	printf("\n");
}
int main()
{
	printf("System Resource Limits:\n\n");

	resource_limit("RLIMIT_CPU\n ", RLIMIT_CPU);
	resource_limit("RLIMIT_FSIZE \n", RLIMIT_FSIZE);	  // size of the file
	resource_limit("RLIMIT_DATA\n ", RLIMIT_DATA);		  // size of the data segment initialized and heap
	resource_limit("RLIMIT_STACK\n ", RLIMIT_STACK);	  // stck size limit
	resource_limit("RLIMIT_RSS ", RLIMIT_RSS);			  // Maximum memory used by process in RAM
	resource_limit("RLIMIT_CORE\n ", RLIMIT_CORE);		  // size of core dumps
	resource_limit("RLIMIT_NPROC\n ", RLIMIT_NPROC);	  // Maximum number of process per user
	resource_limit("RLIMIT_NOFILE\n ", RLIMIT_NOFILE);	  // maximum number of open file descriptor
	resource_limit("RLIMIT_MEMLOCK \n ", RLIMIT_MEMLOCK); // Maximum amount of memory that may be locked into RAM
	resource_limit("RLIMIT_AS\n ", RLIMIT_AS);			  // Address space

	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
System Resource Limits:

RLIMIT_CPU
  Soft limit value= Unlimited
Hard limit value= Unlimited
RLIMIT_FSIZE
 Soft limit value= Unlimited
Hard limit value= Unlimited
RLIMIT_DATA
  Soft limit value= Unlimited
Hard limit value= Unlimited
RLIMIT_STACK
  Soft limit value= 8388608
Hard limit value= Unlimited
RLIMIT_RSS  Soft limit value= Unlimited
Hard limit value= Unlimited
RLIMIT_CORE
  Soft limit value= 0
Hard limit value= Unlimited
RLIMIT_NPROC
  Soft limit value= 62441
Hard limit value= 62441
RLIMIT_NOFILE
  Soft limit value= 1048576
Hard limit value= 1048576
RLIMIT_MEMLOCK
  Soft limit value= 2072035328
Hard limit value= 2072035328
RLIMIT_AS
  Soft limit value= Unlimited
Hard limit value= Unlimited
*/
