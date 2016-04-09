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

/* #define DEBUG_PRINT_TRACE ///< print traces for debugging */

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
    memInfo *cache = (memInfo *) malloc(sizeof(memInfo));

    /* structure containing statistics for simulation */
    performance *stats = malloc(sizeof(performance));
    performance zero = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    *stats = zero; // zero all elements in stats

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

    /* calculate cost based on cache configuration */
    calculateCost(cache);

    /* calulate number of tag bits and index bits for the cache configuration */
    calcBits(cache, &bitsIndexL1, &bitsTagL1, &bitsIndexL2, &bitsTagL2);

    /* TODO Initialize caches */
    int i,j;
    int numLines = 256;
    int numWays = 1;
    block **line = malloc(numLines * sizeof(block*));
    for(i=0; i<numLines; i++)
        line[i] = malloc(numLines * sizeof(block));
    for(i=0; i<numLines; i++)
    {
        blockNode *firstNode = malloc(sizeof(blockNode));
        line[i]->first = firstNode;
        line[i]->last = firstNode;
        line[i]->nodeCount = 1;
        for(j=0; j<numWays; j++)
        {
            blockNode *node = malloc(sizeof(blockNode));
            node->valid = 0;
            node-> dirty = 0;
            node->tag = 0;
            node->next = NULL;
            line[i]->last->next = node;
            node->prev = line[i]->last;
            line[i]->last = node;
            line[i]->nodeCount++;
        }
    }

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
                printf("ERROR: invalid trace operation\n");
                return EXIT_FAILURE;
                break;
        }

         /* loop for L1 access - 4 byte bus -> multiple accesses possible */
        while(currAddr <= endAddr)
        {
            /* index and tag for the address */
            currIndxL1 = (currAddr << bitsTagL1) >> (bitsTagL1 + L1_OFFSET);
            currIndxL2 = (currAddr << bitsTagL2) >> (bitsTagL2 + L2_OFFSET);
            currTagL1 = currAddr >> (bitsIndexL1 + L1_OFFSET);
            currTagL2 = currAddr >> (bitsIndexL2 + L2_OFFSET);

            /* alternative methods (untested) */
            /* currIndxL1 = (currAddr >> L1_OFFSET) | (2^(bitsIndexL1+1) - 1); */
            /* currIndxL1 = (currAddr / mem->L1dBlock) % (mem->L1dSize / mem->L1dBlock); */
            /* currTagL1 = currAddr >> (64 - ((int)log2(mem->L1dSize / mem->L1dBlock) + (int)log2(mem->L1dBlock))); */

            /* perform action based on type of reference (instruction, data read, data write) */
            switch(op)
            {
                // TODO how access cache global or pass to function
                case 'I':
                    if(checkL1i(currIndxL1, currTagL1) == HIT)
                    {
                        /* increment statistics for simulation */
                        stats->hitL1i++;
                        stats->cycleInst += L1_HIT_TIME;
                    }
                    else
                    {
                        /* check up the memory hierarchy for the requested value */
                        L1iMiss(currTagL1, currTagL2, currIndxL1, currIndxL2);
                    }
                    break;
                case 'R':
                    if(checkL1d(currIndxL1, currTagL1) == HIT)
                    {
                        /* increment statistics for simulation */
                        stats->hitL1d++;
                        stats->cycleDRead += L1_HIT_TIME;
                    }
                    else
                    {
                        /* check up the memory hierarchy for the requested value */
                        L1dMiss(currTagL1, currTagL2, currIndxL1, currIndxL2, CLEAN);
                    }
                    break;
                case 'W':
                    if(checkL1d(currIndxL1, currTagL1) == HIT)
                    {
                        /* increment statistics for simulation */
                        stats->hitL1d++;
                        stats->cycleDWrite += L1_HIT_TIME;
                    }
                    else
                    {
                        /* check up the memory hierarchy for the requested value */
                        L1dMiss(currTagL1, currTagL2, currIndxL1, currIndxL2, DIRTY);
                    }
                    break;
                default:
                    printf("ERROR: invalid trace operation\n");
                    return EXIT_FAILURE;
                    break;
            }

            /* increment to next address */
            currAddr += 4;
        }
    }

    /* free any allocated memory */
    free(cache);
    free(stats);

    // free linked list memory
    for(i=0; i<numLines; i++)
    {
        blockNode *temp1 = line[i]->first;
        blockNode *temp2;
        while(temp1 != NULL)
        {
            temp2 = temp1;
            temp1 = temp1->next;
            free(temp2);
        }
        free(line[i]);
    }
    free(line);

    return EXIT_SUCCESS;
}
