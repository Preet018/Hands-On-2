/*
=====================================================================================================================================================================================
Name: 3.c
Author: Preet Chandrakar
Description: Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: September 11, 2025
======================================================================================================================================================================================
*/

#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <errno.h>

int main()
{
	struct rlimit res_limit, new_res_limit;

	if (getrlimit(RLIMIT_FSIZE, &res_limit) == 0)
	{
		printf("Old RLIMIT_FSIZE limits: soft = %ld, hard = %ld\n", res_limit.rlim_cur, res_limit.rlim_max);
	}
	else
	{
		fprintf(stderr, "Failed to retrieve old limits: %s\n", strerror(errno));
		return 1;
	}

	// setting new resource limit
	new_res_limit.rlim_cur = 10;
	new_res_limit.rlim_max = 20; // 10 open file descriptor

	if (setrlimit(RLIMIT_FSIZE, &new_res_limit) == 0)
	{
		printf("Setting new limit: Successfully done");
	}
	else
	{
		fprintf(stderr, "Setting new limits unsuccessful: %s\n", strerror(errno)); // handles error appropriately if limit fails

		return 1;
	}

	// Verifying new limits
	if (getrlimit(RLIMIT_FSIZE, &new_res_limit) == 0)
	{
		printf("\nNew RLIMIT_FSIZE limits: soft = %ld, hard = %ld\n", new_res_limit.rlim_cur, new_res_limit.rlim_max);
	}
	else
	{
		fprintf(stderr, "Failed to retrieve new limits: %s\n", strerror(errno));
		return 1;
	}
	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Old RLIMIT_FSIZE limits: soft = -1, hard = -1
Setting new limit: Successfully done
New RLIMIT_FSIZE limits: soft = 10, hard = 20
 */
