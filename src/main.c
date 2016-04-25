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

/* #define DEBUG_PRINT_TRACE    ///< print traces for debugging */
/* #define READ_FILE            ///< read trace from a file rather than use zcat */
/* #define PRINT_STATS          ///< print statistics to stdout */

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
    char traceName[128];         // temp buffer to hold the trace name

    /* structure containing cache settings */
    memInfo *cacheCnfg = (memInfo *) malloc(sizeof(memInfo));
    if(cacheCnfg == NULL)
        PERR("malloc error");

    /* structure containing statistics for simulation */
    performance *stats = malloc(sizeof(performance));
    if(stats == NULL)
        PERR("malloc errro");
    performance zero = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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
    if(argc >= 2)
    {
        strcpy(cacheCnfg->cacheName,argv[1]);
        /* Set the values from the file */
        if( setCacheValues(cacheCnfg) )
            PERR("config issue: error setting values");
    }
    else
    {
        /***** Default cache values *****/
        strcpy(cacheCnfg->cacheName,"../config/default.txt");

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

    /* get the config name from the config file passed in */
    getName(cacheCnfg->cacheName);
    printf("config: %s\n",cacheCnfg->cacheName);

    /* get the trace name from the second argv */
    for(unsigned long x=0; x<strlen(argv[2]); x++)
        traceName[x] = argv[2][x];
    getName(traceName);
    printf("trace: %s\n\n", traceName);

#ifdef DEBUG_PRINT_TRACE
    ulli j = 0;
#endif

#ifdef READ_FILE
    FILE *fp;
    fp = fopen("../traces/traces_5M/sjeng.txt", "r");
    /* read a trace from stdin and print it */
    while(fscanf(fp, "%c %llx %d\n", &op, &addr, &numBytes) == 3)
#else
    while(readTrace(&op, &addr, &numBytes) == EXIT_SUCCESS)
#endif
    {
#ifdef DEBUG_PRINT_TRACE
        if(j%1000000 == 0)
            printf("ref:%llu %llu %c\n",j,addr, op);
        j++;
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
        while(currAddr <= endAddr)
        {
            /* index and tag for the address */
            currIndxL1 = (currAddr << cacheCnfg->bitsTagL1) >> (cacheCnfg->bitsTagL1 + L1_OFFSET);
            currIndxL2 = (currAddr << cacheCnfg->bitsTagL2) >> (cacheCnfg->bitsTagL2 + L2_OFFSET);
            currTagL1 = currAddr >> (cacheCnfg->bitsIndexL1 + L1_OFFSET);
            currTagL2 = currAddr >> (cacheCnfg->bitsIndexL2 + L2_OFFSET);

            /* alternative methods (untested) */
            /* currIndxL1 = (currAddr >> L1_OFFSET) | (2^(bitsIndexL1+1) - 1); */
            /* currIndxL1 = (currAddr / mem->L1dBlock) % (mem->L1dSize / mem->L1dBlock); */
            /* currTagL1 = currAddr >> (64 - ((int)log2(mem->L1dSize / mem->L1dBlock) + (int)log2(mem->L1dBlock))); */

            /* perform action based on type of reference (instruction, data read, data write) */
            switch(op)
            {
                case 'I':
                    stats->misAlInstRef++;
                    if(checkL1i(currIndxL1, currTagL1, cacheHier) == HIT)
                    {
                        /* increment statistics for simulation */
                        stats->hitL1i++;
                        stats->cycleInst += L1_HIT_T;
                    }
                    else
                    {
                        /* increment miss count */
                        stats->missL1i++;
                        stats->cycleInst += L1_MISS_T;

                        /* check up the memory hierarchy for the requested value */
                        if(L1iMiss(stats, cacheCnfg,  currTagL1, currTagL2, currIndxL1, currIndxL2, cacheHier, currAddr) == EXIT_FAILURE)
                            PERR("L1i miss issue");
                    }
                    break;
                case 'R':
                    stats->misAlDReadRef++;
                    if(checkL1dR(currIndxL1, currTagL1, cacheHier) == HIT)
                    {
                        /* increment statistics for simulation */
                        stats->hitL1d++;
                        stats->cycleDRead += L1_HIT_T;
                    }
                    else
                    {
                        /* increment miss count */
                        stats->missL1d++;
                        stats->cycleDRead += L1_MISS_T;

                        /* check up the memory hierarchy for the requested value */
                        if(L1dMiss(stats, cacheCnfg,  currTagL1, currTagL2, currIndxL1, currIndxL2, cacheHier, addr, READ, dataTR) == EXIT_FAILURE)
                            PERR("L1d write miss issue");
                    }
                    break;
                case 'W':
                    stats->misAlDWriteRef++;
                    if(checkL1dW(currIndxL1, currTagL1, cacheHier) == HIT)
                    {
                        /* increment statistics for simulation */
                        stats->hitL1d++;
                        stats->cycleDWrite += L1_HIT_T;
                    }
                    else
                    {
                        /* increment miss count */
                        stats->missL1d++;
                        stats->cycleDWrite += L1_MISS_T;

                        /* check up the memory hierarchy for the requested value */
                        if(L1dMiss(stats, cacheCnfg,  currTagL1, currTagL2, currIndxL1, currIndxL2, cacheHier, addr, WRITE, dataTW) == EXIT_FAILURE)
                            PERR("L1d miss issue");
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
            }
    }

    // print the simulation results to a file in sim_results/
    printResults(traceName,cacheCnfg,stats);

#ifdef PRINT_STATS
    // print the cache contents
    printCurrCache(cacheCnfg, cacheHier);

    printf("inst refs: %llu\n",stats->instRefs);
    printf("data R refs: %llu\n",stats->dataReadRef);
    printf("data W refs: %llu\n",stats->dataWriteRef);

    printf("\n\nhits L1i: %llu\n",stats->hitL1i);
    printf("miss L1i: %llu\n",stats->missL1i);
    printf("L1i kick: %llu\n", stats->kickoutL1i);
    printf("VCL1i hit: %llu\n\n", stats->VChitL1i);

    printf("hits L1d: %llu\n",stats->hitL1d);
    printf("miss L1d: %llu\n",stats->missL1d);
    printf("L1d kick: %llu\n", stats->kickoutL1d);
    printf("L1d dirty kick: %llu\n", stats->dirtyKickL1d);
    printf("VCL1d hit: %llu\n\n", stats->VChitL1d);

    printf("hits L2: %llu\n",stats->hitL2);
    printf("miss L2: %llu\n",stats->missL2);
    printf("L2 kick: %llu\n", stats->kickoutL2);
    printf("L2 dirty kick: %llu\n", stats->dirtyKickL2);
    printf("VCL2 hit: %llu\n\n", stats->VChitL2);

    printf("\ncycles data read: %llu\n", stats->cycleDRead);
    printf("cycles data write: %llu\n", stats->cycleDWrite);
    printf("cycles inst: %llu\n", stats->cycleInst);
    printf("total exec. time: %llu\n", stats->cycleInst+stats->cycleDRead+stats->cycleDWrite);
#endif

    // free cache memory
    deleteCache(cacheCnfg, cacheHier);
    free(cacheHier);

    /* free any allocated memory */
    free(cacheCnfg);
    free(stats);

#ifdef READ_FILE
    fclose(fp);
#endif

    return EXIT_SUCCESS;
}
