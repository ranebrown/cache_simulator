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

int calcBits(memInfo *mem)
{
    if(mem == NULL)
        PERR("null value passed");

    // handle fully associative case for L1 cache
    if(mem->L1iWays == 0)
    {
        // number of index bits L1 cache
        mem->bitsIndexL1 = 0;

        // number of tag bits L1 cache
        mem->bitsTagL1 = 64 - L1_OFFSET;

    }
    // all other configurations
    else
    {
        // number of index bits L1 cache
        mem->bitsIndexL1 = log2((mem->L1dSize / mem->L1dBlock) / mem->L1dWays);

        // number of tag bits L1 cache
        mem->bitsTagL1 = 64 - mem->bitsIndexL1 - L1_OFFSET;
    }

    // handle fully associative case for L2 cache
    if(mem->L2Ways == 0)
    {
        // number of index bits L2 cache
        mem->bitsIndexL2 = 0;

        // number of tag bits L2 cache
        mem->bitsTagL2 = 64 - L2_OFFSET;
    }
    // all other configurations
    else
    {
        // number of index bits L2 cache
        mem->bitsIndexL2 = log2((mem->L2Size / mem->L2Block) / mem->L2Ways);

        // number of tag bits L2 cache
        mem->bitsTagL2 = 64 - mem->bitsIndexL2 - L2_OFFSET;
    }

    return EXIT_SUCCESS;
}

int printCurrCache(memInfo *cacheCnfg, allCache *cacheHier)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
        PERR("cache not initialized");

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

    node *L1iNode      =    NULL;
    node *L1dNode      =    NULL;
    node *L2Node       =    NULL;
    node *VCL1iNode    =    NULL;
    node *VCL1dNode    =    NULL;
    node *VCL2Node     =    NULL;

    // print L1i cache values
    printf("L1i\n");
    for(i=0; i<numLinesL1; i++)
    {
        L1iNode = cacheHier->L1i[i]->first;
        printf("Index: %3x | ", i);
        for(j=0; j<numWaysL1; j++)
        {
            if(L1iNode->valid == 1)
            {
                printf("D: %x | ", L1iNode->dirty);
                printf("Tag: %10llx\t", L1iNode->tag);
            }
            L1iNode = L1iNode->next;
        }
        printf("\n");
    }

    // print L1d cache values
    printf("\nL1d\n");
    for(int i=0; i<numLinesL1; i++)
    {
        L1dNode = cacheHier->L1d[i]->first;
        printf("Index: %3x | ", i);
        for(j=0; j<numWaysL1; j++)
        {
            if(L1dNode->valid == 1)
            {
                printf("D: %x | ", L1dNode->dirty);
                printf("Tag: %10llx\t", L1dNode->tag);
            }
            L1dNode = L1dNode->next;
        }
        printf("\n");
    }

    // print L2 cache values
    printf("\nL2\n");
    for(int i=0; i<numLinesL2; i++)
    {
        L2Node = cacheHier->L2[i]->first;

        printf("Index: %3x | ", i);
        for(j=0; j<numWaysL2; j++)
        {
            if(L2Node->valid == 1)
            {
                printf("D: %x | ", L2Node->dirty);
                printf("Tag: %10llx\t", L2Node->tag);
            }
            L2Node = L2Node->next;
        }
        printf("\n");
    }

    // print Victim cache values
    printf("\nVCL1i\n");
    VCL1iNode = cacheHier->VCL1i->first;
    for(i=0; i<8; i++)
    {
        if(VCL1iNode->valid == 1)
        {
            printf("D: %x | ", VCL1iNode->dirty);
            printf("Tag: %10llx\n", VCL1iNode->tag);
        }
        VCL1iNode = VCL1iNode->next;

    }
    printf("\nVCL1d\n");
    VCL1dNode = cacheHier->VCL1d->first;
    for(i=0; i<8; i++)
    {
        if(VCL1dNode->valid == 1)
        {
            printf("D: %x | ", VCL1dNode->dirty);
            printf("Tag: %10llx\n", VCL1dNode->tag);
        }
        VCL1dNode = VCL1dNode->next;

    }
    printf("\nVCL2\n");
    VCL2Node = cacheHier->VCL2->first;
    for(i=0; i<8; i++)
    {
        if(VCL2Node->valid == 1)
        {
            printf("D: %x | ", VCL2Node->dirty);
            printf("Tag: %10llx\n", VCL2Node->tag);
        }
        VCL2Node = VCL2Node->next;

    }
    printf("\n");

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
