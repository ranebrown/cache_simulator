/**
 * @file        cache.c
 * @authors     Rane Brown & Brian Douglass
 * @date        04-01-2016
 * @brief       Functions shared between cache levels
 *
 * index - a block "line"
 * tag - specific address in a block
 * offset - which byte in the block e.g. a 32 byte block would need 5 bits 2^5 to represent each byte
 * ways - number of chunks the cache is broken into
 * set  - the set of "ways" for a specific block
 */

#include "cache.h"

int calcBits(memInfo *mem, int *bitsIndexL1, int *bitsTagL1, int *bitsIndexL2, int *bitsTagL2)
{
    if(mem == NULL || bitsIndexL1 == NULL || bitsTagL1 == NULL || bitsIndexL2 == NULL || bitsTagL2 == NULL)
        return EXIT_FAILURE;

    // handle fully associative case for L1 cache
    if(mem->L1iWays == 0)
    {
        // number of index bits L1 cache
        *bitsIndexL1 = 0;

        // number of tag bits L1 cache
        *bitsTagL1 = 64 - L1_OFFSET;

    }
    // all other configurations
    else
    {
        // number of index bits L1 cache
        *bitsIndexL1 = log2((mem->L1dSize / mem->L1dBlock) / mem->L1dWays);

        // number of tag bits L1 cache
        *bitsTagL1 = 64 - *bitsIndexL1 - L1_OFFSET;
    }

    // handle fully associative case for L2 cache
    if(mem->L2Ways == 0)
    {
        // number of index bits L2 cache
        *bitsIndexL2 = 0;

        // number of tag bits L2 cache
        *bitsTagL2 = 64 - L2_OFFSET;
    }
    // all other configurations
    else
    {
        // number of index bits L2 cache
        *bitsIndexL2 = log2((mem->L2Size / mem->L2Block) / mem->L2Ways);

        // number of tag bits L2 cache
        *bitsTagL2 = 64 - *bitsIndexL2 - L2_OFFSET;
    }

    return EXIT_SUCCESS;
}

int initCache(memInfo *cacheCnfg, allCache *cacheHier)
{
    // NOTE: function assumes L1i and L1d are same size, same # blocks, same # ways

    int i             =    0;
    int j             =    0;
    int numLinesL1    =    0;
    int numLinesL2    =    0;
    int numWaysL1     =    0;
    int numWaysL2     =    0;

    // handle fully associative case L1
    if(cacheCnfg->L1iWays == 0)
    {
        numLinesL1 = 1;
        numWaysL1 = cacheCnfg->L1dSize / cacheCnfg->L1dBlock;
    }
    // all other configurations
    else
    {
        numLinesL1    =    cacheCnfg->L1dSize / cacheCnfg->L1dBlock / cacheCnfg->L1dWays;
        numWaysL1     =    cacheCnfg->L1dWays;
    }
    // handle fully associative case L2
    if(cacheCnfg->L2Ways == 0)
    {
        numLinesL2 = 1;
        numWaysL2 = cacheCnfg->L2Size / cacheCnfg->L2Block;
    }
    // all other configurations
    else
    {
        numLinesL2  =   cacheCnfg->L2Size / cacheCnfg->L2Block / cacheCnfg->L2Ways;
        numWaysL2   =   cacheCnfg->L2Ways;
    }

    // allocate memory for fields
    if((cacheHier->L1i = malloc(numLinesL1 * sizeof(list*))) == NULL)
        PERR("malloc failed");
    if((cacheHier->L1d = malloc(numLinesL1 * sizeof(list*))) == NULL)
        PERR("malloc failed");
    if((cacheHier->L2 = malloc(numLinesL2 * sizeof(list*))) == NULL)
        PERR("malloc failed");
    if((cacheHier->VCL1i = malloc(sizeof(list*))) == NULL)
        PERR("malloc failed");
    if((cacheHier->VCL1d = malloc(sizeof(list*))) == NULL)
        PERR("malloc failed");
    if((cacheHier->VCL2 = malloc(sizeof(list*))) == NULL)
        PERR("malloc failed");

    // initialize L1 caches
    for(i=0; i< numLinesL1; i++)
    {
        // create number of lines
        cacheHier->L1i[i] = initList(numWaysL1);
        cacheHier->L1d[i] = initList(numWaysL1);

        // create number of ways
        for(j=0; j<numWaysL1; j++)
        {
            if(putFirst(cacheHier->L1i[i]) == EXIT_FAILURE)
                PERR("putFirst failed");
            if(putFirst(cacheHier->L1d[i]) == EXIT_FAILURE)
                PERR("putFirst failed");
        }
    }

    // initialize L2 cache
    for(i=0; i<numLinesL2; i++)
    {
        // create number of lines
        cacheHier->L2[i] = initList(numWaysL2);

        // create number of ways
        for(j=0; j<numWaysL2; j++)
        {
            if(putFirst(cacheHier->L2[i]) == EXIT_FAILURE)
                PERR("putFirst failed");
        }
    }

    // initialize victim caches
    // create number of lines (one for each VC)
    cacheHier->VCL1i = initList(8);
    cacheHier->VCL1d = initList(8);
    cacheHier->VCL2 = initList(8);
    for(i=0; i<8; i++)
    {
        if(putFirst(cacheHier->VCL1i) == EXIT_FAILURE)
            PERR("putFirst failed");
        if(putFirst(cacheHier->VCL1d) == EXIT_FAILURE)
            PERR("putFirst failed");
        if(putFirst(cacheHier->VCL2) == EXIT_FAILURE)
            PERR("putFirst failed");
    }

    return EXIT_SUCCESS;
}

int deleteCache(memInfo *cacheCnfg, allCache *cacheHier)
{
    int i             =    0;
    int numLinesL1    =    0;
    int numLinesL2    =    0;

    // handle fully associative case L1
    if(cacheCnfg->L1iWays == 0)
        numLinesL1 = 1;
    // all other configurations
    else
        numLinesL1    =    cacheCnfg->L1dSize / cacheCnfg->L1dBlock / cacheCnfg->L1dWays;
    // handle fully associative case L2
    if(cacheCnfg->L2Ways == 0)
        numLinesL2 = 1;
    // all other configurations
    else
        numLinesL2    =    cacheCnfg->L2Size / cacheCnfg->L2Block / cacheCnfg->L2Ways;

    // delete L1 caches
    for(i=0; i<numLinesL1; i++)
    {
        if(deleteList(cacheHier->L1i[i]) == EXIT_FAILURE)
            PERR("delete list failed");
        if(deleteList(cacheHier->L1d[i]) == EXIT_FAILURE)
            PERR("delete list failed");
    }

    // delete L2 cache
    for(i=0; i<numLinesL2; i++)
    {
        if(deleteList(cacheHier->L2[i]) == EXIT_FAILURE)
            PERR("delete list failed");
    }

    // delete VC caches
    if(deleteList(cacheHier->VCL1i) == EXIT_FAILURE)
        PERR("delete list failed");
    if(deleteList(cacheHier->VCL1d) == EXIT_FAILURE)
        PERR("delete list failed");
    if(deleteList(cacheHier->VCL2) == EXIT_FAILURE)
        PERR("delete list failed");

    return EXIT_SUCCESS;
}
