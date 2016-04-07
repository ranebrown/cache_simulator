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

int main(int argc, char *argv[])
{
    /* Local Variables */
    char op;                            /// type of operation - read or write or instruction
    unsigned long long int addr;        /// memory address
    unsigned int numBytes;              /// number of bytes referenced by request
    int res = 0;                        /// result of trace read

    // structure containing cache settings
    memInfo *cache = (memInfo *) malloc(sizeof(memInfo));

    /* Default values*/
    cache->L1dBlock  = 32;
    cache->L1iBlock  = 32;
    cache->L2Block   = 64;

    /* Main Memory (default values) */
    cache->addrsendT = 10;
    cache->readyT    = 50;
    cache->chunkT    = 15;
    cache->chunkS    = 8;

    /* If there is a file included, it is the config needed */
    if(argc == 2)
    {
        strcpy(cache->cacheName,argv[1]);
        /* Set the values from the file */
        if( setCacheValues(cache) )
        {
            printf("Error setting values.\n");
        }
        else
        {
            printf("\nCache name: %s\n",cache->cacheName);
            printf("Done setting values.\n");
        }
    }
    else
    {
        /***** Default cache values *****/
        strcpy(cache->cacheName,"../config/default.txt");
        printf("\nCache name: %s\n",cache->cacheName);

        /* L1 data */
        cache->L1dWays   = 1;
        cache->L1dSize   = 8192;
        cache->L1dBlock  = 32;

        /* L1 instruction */
        cache->L1iWays   = 1;
        cache->L1iSize   = 8192;
        cache->L1iBlock  = 32;

        /* L2 */
        cache->L2Ways    = 1;
        cache->L2Size    = 32768;
        cache->L2Block   = 64;
    }

    // calculate cost based on cache configuration
    calculateCost(cache);

    // read a trace from stdin and print it
    while(res == 0)
    {
        res = readTrace(&op, &addr, &numBytes);
        if(res == 0)
        {
            printf("%c %llx %d\n" ,op ,addr ,numBytes);
        }
    }

    // free any allocated memory
    free(cache);

    return EXIT_SUCCESS;
}
