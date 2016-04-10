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
     * @param[in] addr address being checked
     * @return 0 hit, 1 miss
     */
    int checkL2(ulli currTag, ulli currIndx, allCache *cacheHier);

    int L2miss(ulli currTagL2, ulli currIndxL2, allCache *cacheHier);

#endif // L2_CACHE_H
