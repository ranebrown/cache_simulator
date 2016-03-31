/**
 * @file        readTrace.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-23-2016
 * @brief       Source file containing functions for reading a trace from stdin
 */

#include "readTrace.h"

int readTrace(char *op, unsigned long long int *addr, unsigned int *bs)
{
    // result of scanf
    int res;

    // variables used to timeout if no input from stdin
    fd_set rfds;
    struct timeval tv;
    int retval;

    // Watch stdin (fd 0) to see when it has input.
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    // wait up to 2 seconds for input
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    // select function returns status
    retval = select(1, &rfds, NULL, NULL, &tv);

    if (retval == -1)   // error with select function
    {
        perror("select()");
        return EXIT_FAILURE;
    }
    else if (retval)    // data is ready to be read
    {
        // read a trace from stdin
        res = scanf("%c %llx %d\n", op, addr, bs);
        if(res == 3)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else
    {
        printf("Trace read timeout\n");
        return EXIT_FAILURE;
    }
}
