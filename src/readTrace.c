/**
 * @file        readTrace.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-23-2016
 * @brief       Source file containing functions for reading a trace from stdin
 */

#include "readTrace.h"

int readTrace(char *op, unsigned long long int *addr, unsigned int *bs)
{
    int res;                            /// result of scan

    // read a trace from stdin
    res = scanf("%c %Lx %d\n", op, addr, bs);

    if(res == 3)
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}
