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
#include "cache.h"
#include "L1cache.h"
#include "L2cache.h"
#include "dlinkedList.h"

/* #define DEBUG_PRINT_TRACE ///< print traces for debugging */
/* #define DEBUG_ADDR ///< print the tag and index info */
/* #define DEBUG_MAIN */

/**
 * @brief main function for cache simulator
 */
int main(int argc, char *argv[])
{
    /* Local Variables */
    char op         =   0;      // type of operation - read or write or instruction
    ulli addr       =   0;      // memory address
    ui numBytes     =   0;      // number of bytes referenced by request
    ui currIndxL1   =   0;      // cache index for an address
    ui currIndxL2   =   0;      // cache index for an address
    ulli currTagL1  =   0;      // cache tag for an address
    ulli currTagL2  =   0;      // cache tag for an address
    ulli currAddr   =   0;      // address from trace
    ulli endAddr    =   0;      // end address from trace (depends on number of bytes)

    /* structure containing cache settings */
    memInfo *cacheCnfg = (memInfo *) malloc(sizeof(memInfo));
    if(cacheCnfg == NULL)
        PERR("malloc error");

    /* structure containing statistics for simulation */
    performance *stats = malloc(sizeof(performance));
    if(stats == NULL)
        PERR("malloc errro");
    performance zero = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    *stats = zero; // zero all elements in stats

    /* structure used to represent each cache level (doubly linked list) */
    allCache *cacheHier = malloc(sizeof(allCache));
    if(cacheHier == NULL)
        PERR("malloc error");

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
            PERR("config issue: error setting values");
        else
        {
            printf("\nCache name: %s\n",cacheCnfg->cacheName);
            printf("Done setting values.\n");
        }
    }
    else
    {
        /***** Default cache values *****/
        strcpy(cacheCnfg->cacheName,"../config/default.txt");
        printf("\nCache name: %s\n",cacheCnfg->cacheName);

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
    }

    /* calculate cost based on cache configuration */
    calculateCost(cacheCnfg);

    /* calulate number of tag bits and index bits for the cache configuration */
    calcBits(cacheCnfg);

    // initialize and allocate memory for all cache levels
    initCache(cacheCnfg, cacheHier);

    int i = 0;
    /* read a trace from stdin and print it */
    while(readTrace(&op, &addr, &numBytes) == EXIT_SUCCESS)
    {
#ifdef DEBUG_PRINT_TRACE
            printf("%c %llx %d\n" ,op ,addr ,numBytes);
#endif

        /* calculate the word (4 byte) aligned start address */
        currAddr = addr & 0xFFFFFFFFFFFFFFFC;

        /* calculate the end address (doesn't need to be word aligned since currAddr is incremented by 4) */
        endAddr = addr + numBytes-1;

        /* update the stats for the number of references */
        switch(op)
        {
            case 'I':
                stats->instRefs++;
                break;
            case 'R':
                stats->dataReadRef++;
                break;
            case 'W':
                stats->dataWriteRef++;
                break;
            default:
                PERR("invalid trace operation");
        }
         /* loop for L1 access - 4 byte bus -> multiple accesses possible */

            printf("ref:%d-------------------------------------------\n",i);
            i++;
        while(currAddr <= endAddr)
        {
            /* index and tag for the address */
            currIndxL1 = (currAddr << cacheCnfg->bitsTagL1) >> (cacheCnfg->bitsTagL1 + L1_OFFSET);
            currIndxL2 = (currAddr << cacheCnfg->bitsTagL2) >> (cacheCnfg->bitsTagL2 + L2_OFFSET);
            currTagL1 = currAddr >> (cacheCnfg->bitsIndexL1 + L1_OFFSET);
            currTagL2 = currAddr >> (cacheCnfg->bitsIndexL2 + L2_OFFSET);

#ifdef DEBUG_ADDR
            printf("current address: %llu\n",currAddr);
            printf("current index: %d\n",currIndxL1);
            printf("current tag: %llu\n",currTagL1);
#endif

            /* alternative methods (untested) */
            /* currIndxL1 = (currAddr >> L1_OFFSET) | (2^(bitsIndexL1+1) - 1); */
            /* currIndxL1 = (currAddr / mem->L1dBlock) % (mem->L1dSize / mem->L1dBlock); */
            /* currTagL1 = currAddr >> (64 - ((int)log2(mem->L1dSize / mem->L1dBlock) + (int)log2(mem->L1dBlock))); */

            /* perform action based on type of reference (instruction, data read, data write) */
            switch(op)
            {
                case 'I':
                    if(checkL1i(currIndxL1, currTagL1, cacheHier) == HIT)
                    {
                        /* increment statistics for simulation */
                        stats->hitL1i++;
                        stats->cycleInst += L1_HIT_T + 1; // TODO +1 is time to execute inst. move to header?
                        #ifdef POINT_COUNT
                            printf(" 0:L1i hit: \t\t\ttime +1\n");
                        #endif
                    }
                    else
                    {
                        /* increment miss count */
                        stats->missL1i++;
                        stats->cycleInst += L1_MISS_T;
                        #ifdef POINT_COUNT
                            printf(" 1:L1i miss: \t\t\ttime +1\n");
                        #endif


                        /* check up the memory hierarchy for the requested value */
                        if(L1iMiss(stats, cacheCnfg,  currTagL1, currTagL2, currIndxL1, currIndxL2, cacheHier, currAddr) == EXIT_FAILURE)
                            PERR("L1i miss issue");

                        /* Account for the 'replay' time */
                        stats->cycleInst += L1_HIT_T;
                        #ifdef POINT_COUNT
                            printf(" 2:L1i replay: \t\t\ttime +1\n");
                        #endif

                    }
                    break;
                case 'R':
                    if(checkL1dR(currIndxL1, currTagL1, cacheHier) == HIT)
                    {
                        /* increment statistics for simulation */
                        stats->hitL1d++;
                        stats->cycleDRead += L1_HIT_T;
                        #ifdef POINT_COUNT
                            printf(" 3:L1d read  hit: \t\t\ttime +1\n");
                        #endif
                    }
                    else
                    {
                        /* increment miss count */
                        stats->missL1d++;
                        stats->cycleDRead += L1_MISS_T;
                        #ifdef POINT_COUNT
                            printf(" 4:L1d read miss: \t\t\ttime +1\n");
                        #endif

                        /* check up the memory hierarchy for the requested value */
                        if(L1dMiss(stats, cacheCnfg,  currTagL1, currTagL2, currIndxL1, currIndxL2, cacheHier, addr, READ) == EXIT_FAILURE)
                            PERR("L1d miss issue");

                        /* Account for the 'replay' time */
                        stats->cycleDRead += L1_HIT_T;
                        #ifdef POINT_COUNT
                            printf(" 5:L1d read replay: \t\t\ttime +1\n");
                        #endif
                        }
                    break;
                case 'W':
                    if(checkL1dW(currIndxL1, currTagL1, cacheHier) == HIT)
                    {
                        /* increment statistics for simulation */
                        stats->hitL1d++;
                        stats->cycleDWrite += L1_HIT_T;
                        #ifdef POINT_COUNT
                            printf(" 6:L1d write: \t\t\ttime +1\n");
                        #endif
                    }
                    else
                    {
                        /* increment miss count */
                        stats->missL1d++;
                        stats->cycleDRead += L1_MISS_T;
                        #ifdef POINT_COUNT
                            printf(" 7:L1d write miss: \t\ttime +1\n");
                        #endif

                        /* check up the memory hierarchy for the requested value */
                        if(L1dMiss(stats, cacheCnfg,  currTagL1, currTagL2, currIndxL1, currIndxL2, cacheHier, addr, WRITE) == EXIT_FAILURE)
                            PERR("L1d miss issue");
                        /* Account for the 'replay' time */
                        #ifdef POINT_COUNT
                            printf(" 8:L1d write replay: \t\ttime +1\n");
                        #endif
                        stats->cycleDWrite += L1_HIT_T;
                    }
                    break;
                default:
                    PERR("invalid trace operation");
            }

            /* increment to next address */
            currAddr += 4;
        }
            if(op == 'I')
            {
                stats->cycleInst += L1_HIT_T; // to execute inst.
                #ifdef POINT_COUNT
                    printf(" 9:execute inst: \t\ttime +1\n");
                #endif
            }
            printf("total exec. time: %llu\n", stats->cycleInst+stats->cycleDRead+stats->cycleDWrite);
    }

    printf("end-----------------------------------\n");

    /* printCurrCache(cacheCnfg, cacheHier); */

    /* printf("inst refs: %llu\n",stats->instRefs); */
    /* printf("data R refs: %llu\n",stats->dataReadRef); */
    /* printf("data W refs: %llu\n",stats->dataWriteRef); */

    /* printf("\n\nhits L1i: %llu\n",stats->hitL1i); */
    /* printf("miss L1i: %llu\n",stats->missL1i); */
    /* printf("L1i kick: %llu\n", stats->kickoutL1i); */
    /* printf("VCL1i hit: %llu\n\n", stats->VChitL1i); */

    /* printf("hits L1d: %llu\n",stats->hitL1d); */
    /* printf("miss L1d: %llu\n",stats->missL1d); */
    /* printf("L1d kick: %llu\n", stats->kickoutL1d); */
    /* printf("L1d dirty kick: %llu\n", stats->dirtyKickL1d); */
    /* printf("VCL1d hit: %llu\n\n", stats->VChitL1d); */

    /* printf("hits L2: %llu\n",stats->hitL2); */
    /* printf("miss L2: %llu\n",stats->missL2); */
    /* printf("L2 kick: %llu\n", stats->kickoutL2); */
    /* printf("L2 dirty kick: %llu\n", stats->dirtyKickL2); */
    /* printf("VCL2 hit: %llu\n\n", stats->VChitL2); */

    printf("\ncycles inst: %llu\n", stats->cycleInst);
    printf("cycles data read: %llu\n", stats->cycleDRead);
    printf("cycles data write: %llu\n", stats->cycleDWrite);
    printf("total exec. time: %llu\n", stats->cycleInst+stats->cycleDRead+stats->cycleDWrite);


    /* free any allocated memory */
    free(cacheCnfg);
    free(stats);

    // free cache memory
    deleteCache(cacheCnfg, cacheHier);

    free(cacheHier);

    return EXIT_SUCCESS;
}
