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
#include "VCache.h"
#include "dlinkedList.h"

/* #define DEBUG_PRINT_TRACE ///< print traces for debugging */
/* #define DEBUG_ADDR */

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
    int bitsIndexL1 =   0;      // number of bits for L1 index
    int bitsTagL1   =   0;      // number of bits for L1 tag
    int bitsIndexL2 =   0;      // number of bits for L2 index
    int bitsTagL2   =   0;      // number of bits for L2 tag

    /* structure containing cache settings */
    memInfo *cacheCnfg = (memInfo *) malloc(sizeof(memInfo));

    /* structure containing statistics for simulation */
    performance *stats = malloc(sizeof(performance));
    performance zero = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    *stats = zero; // zero all elements in stats

    /* structure used to represent each cache level (doubly linked list) */
    allCache *cacheHier = malloc(sizeof(allCache));
    cacheHier->VCL1i = NULL;
    cacheHier->VCL1d = NULL;
    cacheHier->VCL2 = NULL;
    cacheHier->L1i = NULL;
    cacheHier->L1d = NULL;
    cacheHier->L2 = NULL;

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
    calcBits(cacheCnfg, &bitsIndexL1, &bitsTagL1, &bitsIndexL2, &bitsTagL2);

    /* TODO Initialize caches (write functions) */
    /* initCache(cacheCnfg, cacheHier); */
    int i,j;
    int numLines = cacheCnfg->L1dSize / cacheCnfg->L1dBlock / cacheCnfg->L1dWays;
    int numWays = cacheCnfg->L1dWays;
    list **L1i = malloc(numLines * sizeof(list*));
    for(i=0; i<numLines; i++)
        L1i[i] = malloc(sizeof(list));
    for(i=0; i<numLines; i++)
    {
        node *firstNode = malloc(sizeof(node));
        L1i[i]->first = firstNode;
        L1i[i]->last = firstNode;
        L1i[i]->nodeCount = 1;
        for(j=0; j<numWays; j++)
        {
            node *node = malloc(sizeof(node));
            node->valid = 0;
            node-> dirty = 0;
            node->tag = 0;
            node->next = NULL;
            L1i[i]->last->next = node;
            node->prev = L1i[i]->last;
            L1i[i]->last = node;
            L1i[i]->nodeCount++;
        }
    }
    cacheHier->L1i = L1i;

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
                printf("ERROR: invalid trace operation in %s function: %s: line %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
        }

         /* loop for L1 access - 4 byte bus -> multiple accesses possible */
        while(currAddr <= endAddr)
        {
            /* index and tag for the address */
            currIndxL1 = (currAddr << bitsTagL1) >> (bitsTagL1 + L1_OFFSET);
            currIndxL2 = (currAddr << bitsTagL2) >> (bitsTagL2 + L2_OFFSET);
            currTagL1 = currAddr >> (bitsIndexL1 + L1_OFFSET);
            currTagL2 = currAddr >> (bitsIndexL2 + L2_OFFSET);

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
                        stats->cycleInst += L1_HIT_TIME;
                    }
                    else
                    {
                        /* increment miss count */
                        stats->missL1i++;

                        /* check up the memory hierarchy for the requested value */
                        if(L1iMiss(stats, currTagL1, currTagL2, currIndxL1, currIndxL2, cacheHier) == EXIT_FAILURE)
                        {
                            printf("ERROR: %s: %d", __FILE__, __LINE__);
                            return EXIT_FAILURE;
                        }
                    }
                    break;
                case 'R':
                    if(checkL1dR(currIndxL1, currTagL1, cacheHier) == HIT)
                    {
                        /* increment statistics for simulation */
                        stats->hitL1d++;
                        stats->cycleDRead += L1_HIT_TIME;
                    }
                    else
                    {
                        /* increment miss count */
                        stats->missL1d++;

                        /* check up the memory hierarchy for the requested value */
                        if(L1dMiss(currTagL1, currTagL2, currIndxL1, currIndxL2, cacheHier,  CLEAN) == EXIT_FAILURE)
                        {
                            printf("ERROR: %s: %d", __FILE__, __LINE__);
                            return EXIT_FAILURE;
                        }
                    }
                    break;
                case 'W':
                    if(checkL1dW(currIndxL1, currTagL1, cacheHier) == HIT)
                    {
                        /* increment statistics for simulation */
                        stats->hitL1d++;
                        stats->cycleDWrite += L1_HIT_TIME;
                    }
                    else
                    {
                        /* increment miss count */
                        stats->missL1d++;

                        /* check up the memory hierarchy for the requested value */
                        if(L1dMiss(currTagL1, currTagL2, currIndxL1, currIndxL2, cacheHier, DIRTY) == EXIT_FAILURE)
                        {
                            printf("ERROR: %s: %d", __FILE__, __LINE__);
                            return EXIT_FAILURE;
                        }
                    }
                    break;
                default:
                    printf("ERROR: invalid trace operation in %s: line %d\n", __FILE__, __LINE__);
                    return EXIT_FAILURE;
            }

            /* increment to next address */
            currAddr += 4;
        }
    }

    /* free any allocated memory */
    free(cacheCnfg);
    free(stats);

    // free linked list memory
    for(i=0; i<numLines; i++)
    {
        node *temp1 = L1i[i]->first;
        node *temp2;
        while(temp1 != NULL)
        {
            temp2 = temp1;
            temp1 = temp1->next;
            free(temp2);
        }
        free(L1i[i]);
    }
    free(L1i);

    free(cacheHier);

    return EXIT_SUCCESS;
}
