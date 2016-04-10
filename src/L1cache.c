/**
 * @file        L1cache.c
 * @authors     Rane Brown & Brian Douglass
 * @date        04-06-2016
 * @brief       Function for the L1 cache
 */

#include "L1cache.h"

int checkL1i(ui currIndx, ulli currTag, allCache *cacheHier)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
    {
        printf("ERROR: cache not initialized in %s function: %s: line %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    /* get the first block in the list */
    node *tmpNode = cacheHier->L1i[currIndx]->first;

    /* check each way for a hit */
    while(tmpNode != NULL)
    {
        if(tmpNode->valid && tmpNode->tag == currTag)
            return HIT;
        else
            tmpNode = tmpNode->next;
    }
    return MISS;
}

int checkL1dR(ui currIndx, ulli currTag, allCache *cacheHier)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
    {
        printf("ERROR: cache not initialized in %s function: %s: line %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    /* get the first block in the list */
    node *tmpNode = cacheHier->L1d[currIndx]->first;

    /* check each way for a hit */
    while(tmpNode != NULL)
    {
        if(tmpNode->valid && tmpNode->tag == currTag)
            return HIT;
        else
            tmpNode = tmpNode->next;
    }
    return MISS;
}

int checkL1dW(ui currIndx, ulli currTag, allCache *cacheHier)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
    {
        printf("ERROR: cache not initialized in %s function: %s: line %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    /* get the first block in the list */
    node *tmpNode = cacheHier->L1d[currIndx]->first;

    /* check each way for a hit */
    while(tmpNode != NULL)
    {
        if(tmpNode->valid && tmpNode->tag == currTag)
        {
            tmpNode->dirty = DIRTY;
            return HIT;
        }
        else
            tmpNode = tmpNode->next;
    }
    return MISS;
}

int L1iMiss(ulli currTagL1, ulli currTagL2, int currIndxL1, int currIndxL2)
{
    return EXIT_SUCCESS;
}

int L1dMiss(ulli currTagL1, ulli currTagL2, int currIndxL1, int currIndxL2, int dirtyBit)
{
    return EXIT_SUCCESS;
}

int insertL1i(ulli addr)
{
    return EXIT_SUCCESS;
}

int insertL1d(ulli addr)
{
    return EXIT_SUCCESS;
}
