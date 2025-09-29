/*
============================================================================================
 * Name: 13b.c
 * Author: Preet Chandrakar
 * Description: Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.
 * Date: 21st Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

	// Converting string into int
	pid_t pid = atoi(argv[1]);

	if (kill(pid, SIGSTOP) == 0)
	{
		printf("SIGSTOP signal sent to the process %d\n", pid);
	}

	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./13b 10178
SIGSTOP signal sent to the process 10178
*/
