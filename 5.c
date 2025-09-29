/*
=====================================================================================================================================================================================
Name: 5.c
Author: Preet Chandrakar
Description: Write a program to print the system limitation of
                a. maximum length of the arguments to the exec family of functions.
                b. maximum number of simultaneous process per user id.
                c. number of clock ticks (jiffy) per second.
                d. maximum number of open files
                e. size of a page
                f. total number of pages in the physical memory
                g. number of currently available pages in the physical memory.
Date: September 11, 2025
======================================================================================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <errno.h>

int main()
{
        long value;

        // a.
        value = sysconf(_SC_ARG_MAX); // this system call gets the maximum combined length of arguments for the exec() function
        if (value == -1)
        {
                perror("System call failed for Max argument length");
        }
        else
        {
                printf("a. Maximum length of the arguments to the exec: %ld bytes\n", value);
        }

        // b.
        value = sysconf(_SC_CHILD_MAX);
        if (value == -1)
                perror("System call failed for simulatneous process");
        else
                printf("b. maximum number of simultaneous process per user id: %ld\n", value);

        // c.
        value = sysconf(_SC_CLK_TCK);
        if (value == -1)
                perror("system call failed for closk ticks");
        else
                printf("c. number of clock ticks (jiffy) per second: %ld\n", value);

        // d.
        value = sysconf(_SC_OPEN_MAX);
        if (value == -1)
                perror("System call failed for OPEN_MAX");
        else
                printf("d. maximum number of open files: %ld\n", value);

        // e.
        value = sysconf(_SC_PAGESIZE);
        if (value == -1)
                perror("System call failed for Pagesize");
        else
                printf("e. Size of a page: %ld\n", value);

        // f
        // f
        long total_pages = sysconf(_SC_PHYS_PAGES);
        if (total_pages == -1)
                perror(" System call failed for pages");
        else
                printf("f. Total number of physical memory pages: %ld\n", total_pages);

        // g
        long avail_pages = sysconf(_SC_AVPHYS_PAGES);
        if (avail_pages == -1)
        {
                perror("Syatem call failed for avail_pages");
        }
        else
        {
                printf("g. Number of available physical memory pages: %ld\n", avail_pages);
        }

        return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
a. Maximum length of the arguments to the exec: 2097152 bytes
b. maximum number of simultaneous process per user id: 62441
c. number of clock ticks (jiffy) per second: 100
d. maximum number of open files: 1048576
e. Size of a page: 4096
f. Total number of physical memory pages: 4046947
g. Number of available physical memory pages: 2401168
*/
