/*
============================================================================================
 * Name: 19.c
 * Author: Preet Chandrakar
 * Description:Create a FIFO file by
		a. mknod command
		b. mkfifo command
		c. use strace command to find out, which command (mknod or mkfifo) is better.
		c. mknod system call
		d. mkfifo library function
 * Date: 21st Sept, 2025
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/stat.h>

int main()
{
	mknod("myfifo19_5", __S_IFIFO | 0666, 0);
	printf("Fifo created using mknod\n");

	mkfifo("myfifo19_6", 0666);
	printf("fifo created using mkfifo\n");

	return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ mknod myfifo19_mknod p
iiitb@Preet:~/MyLinux/Hands_on_2$ mkfifo myfifo19_mkfifo
iiitb@Preet:~/MyLinux/Hands_on_2$ strace -o mknod_trace.txt mknod myfifo_3 p
iiitb@Preet:~/MyLinux/Hands_on_2$ strace -o mkfifo_trace.txt mkfifo myfifo_4
iiitb@Preet:~/MyLinux/Hands_on_2$ grep mknod mknod_trace.txt
execve("/usr/bin/mknod", ["mknod", "myfifo_3", "p"], 0x7fff40d71cc0 /* 56 vars */
/*) = 0
mknodat(AT_FDCWD, "myfifo_3", S_IFIFO|0666) = 0
iiitb@Preet:~/MyLinux/Hands_on_2$ grep mkfifo mkfifo_trace.txt
execve("/usr/bin/mkfifo", ["mkfifo", "myfifo_4"], 0x7fff750d07f8 /* 56 vars */
/*) = 0
iiitb@Preet:~/MyLinux/Hands_on_2$ gcc 19.c
*/

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Fifo created using mknod
fifo created using mkfifo
*/