/**
 * @file        L2cache.c
 * @authors     Rane Brown & Brian Douglass
 * @date        04-06-2016
 * @brief       Functions for the L2 cache
 */

#include "L2cache.h"

int checkL2(ulli currTag, ulli currIndx, allCache *cacheHier)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
    {
        fprintf(stderr,"ERROR: cache not initialized in %s function: %s: line %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    return HIT;
}

int L2miss(ulli currTagL2, ulli currIndxL2, allCache *cacheHier)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
    {
        fprintf(stderr,"ERROR: cache not initialized in %s function: %s: line %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
