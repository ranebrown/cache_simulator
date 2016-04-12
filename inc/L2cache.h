/**
 * @file        L2cache.h
 * @authors     Rane Brown & Brian Douglass
 * @date        04-06-2016
 * @brief       Function prototypes for the L2 cache
 */

#ifndef L2_CACHE_H
    #define L2_CACHE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include "cache.h"

    /**
     * @brief check reference is a hit or a miss
     * @param[in] currTag the calculated tag for the L2 cache
     * @param[in] currIndx the calculated index for the L2 cache
     * @param[in] cacheHier structure containing pointers to each cache level in the hierarchy
     * @return 0 hit, 1 miss EXIT_FAILURE any other error
     */
    int checkL2(ulli currTag, ulli currIndx, allCache *cacheHier);

    int L2miss(ulli currTagL2, ulli currIndxL2, allCache *cacheHier, performance *stats);

#endif // L2_CACHE_H
