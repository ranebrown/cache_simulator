/**
 * @file        main.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-18-2016
 * @brief       Main file for cache simulator project.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printResults.h"
#include "readTrace.h"
#include "config.h"

/* Global variables */


int main(int argc, char *argv[])
{
    /* Local Variables */
    char op;                            /// type of operation - read or write or instruction
    unsigned long long int addr;        /// memory address
    unsigned int bs;                    /// byte size - number of bytes referenced by request
    int res = -1;                       /// result of trace read
    memInfo *cacheCnfg = malloc(sizeof(memInfo));

    while(res == 0)
    {
        res = readTrace(&op, &addr, &bs);
        printf("%c %llx %d\n" ,op ,addr ,bs);
    }


    //memInfo *cacheCnfg = (memInfo *) malloc(sizeof(memInfo));

    /* Default values*/
    cacheCnfg->L1dBlock  = 32;
    cacheCnfg->L1iBlock  = 32;
    cacheCnfg->L2Block   = 64;

    /* Main Memory (default values) */
    cacheCnfg->addrsendT = 10;
    cacheCnfg->readyT    = 50;
    cacheCnfg->chunkT    = 15;
    cacheCnfg->chunkS    = 8;

    /* If there is a file included, it is the config needed */
    if(argc == 2)
    {
        strcpy(cacheCnfg->cacheName,argv[1]);
        /* Set the values from the file */
        if( setCacheValues(cacheCnfg) )
        {
            printf("Error setting values.\n");
        }
    }
    else
    {
        /***** Default cache values *****/
        strcpy(cacheCnfg->cacheName,"default.txt");

        /* L1 data */
        cacheCnfg->L1dWays   = 1;
        cacheCnfg->L1dSize   = 8192;
        cacheCnfg->L1dBlock  = 32;

        /* L1 instruction */
        cacheCnfg->L1iWays   = 1;
        cacheCnfg->L1iSize   = 8192;
        cacheCnfg->L1iBlock  = 32;

        /* L2 */
        cacheCnfg->L2Ways    = 1;
        cacheCnfg->L2Size    = 32768;
        cacheCnfg->L2Block   = 64;
        strcpy(cacheCnfg->cacheName, "../config/default.txt");
    }

    printf("\nCache name: %s\n",cacheCnfg->cacheName);

    calculateCost(cacheCnfg);

    printf("Done setting values.\n");

    free(cacheCnfg);

    // read a trace from stdin and print it
    res = readTrace(&op, &addr, &bs);
    while(res == 0)
    {
        res = readTrace(&op, &addr, &bs);
        printf("%c %llx %d\n" ,op ,addr ,bs);
    }


    return EXIT_SUCCESS;
}
