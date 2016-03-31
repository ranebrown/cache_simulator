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
    int res = 0;                        /// result of trace read


    while(res == 0)
    {
        res = readTrace(&op, &addr, &bs);
        printf("%c %llx %d\n" ,op ,addr ,bs);
    }


    memInfo *cache = (memInfo *) malloc(sizeof(memInfo));
    cache->L1dWays   = 1;
    temp             = ;
    cache->L1dSize   = pow(2,temp);
    cache->L1dBlock  = 32;          // TODO Is this correct?

    /* L1 instruction */
    cache->L1iWays   = inStr[3]-'0';
    temp             = (inStr[4]-'0')*10 + (inStr[5]-'0');
    cache->L1iSize   = pow(2,temp);
    cache->L1iBlock  = 32;          // TODO Is this correct?

    /* L2 */
    cache->L2Ways    = inStr[6]-'0';
    temp             = (inStr[7]-'0')*10 + (inStr[8]-'0');
    cache->L2Size    = pow(2,temp);
    cache->L2Block   = 64;         // TODO Is this correct?

    /* If there is a file included, it is the config needed */
    if(argc == 2)
    {
        //This works a little more reliably than
        //strcpy for unknown string lengths
        for(int i=0; argv[1][i] != '\0'; i++)
        {
            cache->cacheName[i] = argv[1][i];
        }
    }
    /* Otherwise use the default values */
    else
    {
        strcpy(cache->cacheName,"default.txt");
    }

    printf("\nCache name: %s\n",cache->cacheName);

    if( setCacheValues(cache) )
        printf("Error setting values.\n");



    calculateCost(cache);

    printf("Done setting values.\n");



    return EXIT_SUCCESS;
}
