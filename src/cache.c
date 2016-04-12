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

    // number of index bits L1 cache
    *bitsIndexL1 = log2((mem->L1dSize / mem->L1dBlock) / mem->L1dWays);

    // number of tag bits L1 cache
    *bitsTagL1 = 64 - *bitsIndexL1 - L1_OFFSET;

    // number of index bits L2 cache
    *bitsIndexL2 = log2((mem->L2Size / mem->L2Block) / mem->L2Ways);

    // number of tag bits L2 cache
    *bitsTagL2 = 64 - *bitsIndexL2 - L2_OFFSET;

    return EXIT_SUCCESS;
}

int initCache(memInfo *cacheCnfg, allCache *cacheHier)
{
    int i             =    0;
    int j             =    0;
    int numLinesL1    =    cacheCnfg->L1dSize / cacheCnfg->L1dBlock / cacheCnfg->L1dWays;
    int numLinesL2    =    cacheCnfg->L2Size / cacheCnfg->L2Block / cacheCnfg->L2Ways;

    // allocate memory for fields
    if((cacheHier->L1i = malloc(numLinesL1 * sizeof(list*))) == NULL)
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }
    if((cacheHier->L1d = malloc(numLinesL1 * sizeof(list*))) == NULL)
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }
    if((cacheHier->L2 = malloc(numLinesL2 * sizeof(list*))) == NULL)
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }
    if((cacheHier->VCL1i = malloc(sizeof(list*))) == NULL)
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }
    if((cacheHier->VCL1d = malloc(sizeof(list*))) == NULL)
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }
    if((cacheHier->VCL2 = malloc(sizeof(list*))) == NULL)
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    // initialize L1 caches
    for(i=0; i< numLinesL1; i++)
    {
        // create number of lines
        cacheHier->L1i[i] = initList(cacheCnfg->L1iWays);
        cacheHier->L1d[i] = initList(cacheCnfg->L1dWays);

        // create number of ways
        for(j=0; j<cacheCnfg->L1iWays; j++)
        {
            if(putFirst(cacheHier->L1i[i]) == EXIT_FAILURE)
            {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }
            if(putFirst(cacheHier->L1d[i]) == EXIT_FAILURE)
            {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }
        }
    }

    // initialize L2 cache
    for(i=0; i<numLinesL2; i++)
    {
        // create number of lines
        cacheHier->L2[i] = initList(cacheCnfg->L2Ways);

        // create number of ways
        for(j=0; j<cacheCnfg->L2Ways; j++)
        {
            if(putFirst(cacheHier->L2[i]) == EXIT_FAILURE)
            {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }
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
        {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
        }
        if(putFirst(cacheHier->VCL1d) == EXIT_FAILURE)
        {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
        }
        if(putFirst(cacheHier->VCL2) == EXIT_FAILURE)
        {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int deleteCache(memInfo *cacheCnfg, allCache *cacheHier)
{
    int i             =    0;
    int numLinesL1    =    cacheCnfg->L1dSize / cacheCnfg->L1dBlock / cacheCnfg->L1dWays;
    int numLinesL2    =    cacheCnfg->L2Size / cacheCnfg->L2Block / cacheCnfg->L2Ways;

    // delete L1 caches
    for(i=0; i<numLinesL1; i++)
    {
        if(deleteList(cacheHier->L1i[i]) == EXIT_FAILURE)
        {
            fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
            return EXIT_FAILURE;
        }
        if(deleteList(cacheHier->L1d[i]) == EXIT_FAILURE)
        {
            fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
            EXIT_FAILURE;
        }
    }

    // delete L2 cache
    for(i=0; i<numLinesL2; i++)
    {
        if(deleteList(cacheHier->L2[i]) == EXIT_FAILURE)
        {
            fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
            EXIT_FAILURE;
        }
    }

    // delete VC caches
    if(deleteList(cacheHier->VCL1i) == EXIT_FAILURE)
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        EXIT_FAILURE;
    }
    if(deleteList(cacheHier->VCL1d) == EXIT_FAILURE)
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        EXIT_FAILURE;
    }
    if(deleteList(cacheHier->VCL2) == EXIT_FAILURE)
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
