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
    #include "common.h"

    /**
     * @brief check reference is a hit or a miss
     * @param[in] currTag the calculated tag for the L2 cache
     * @param[in] currIndx the calculated index for the L2 cache
     * @param[in] cacheHier structure containing pointers to each cache level in the hierarchy
     * @return 0 hit, 1 miss EXIT_FAILURE any other error
     */
    int checkL2(ulli currTag, ulli currIndx, allCache *cacheHier);

    /**
     * @brief if a miss occurs in the L2 cache this function is called to check the victim cache.
     *  If the desired tag is not in the victim cache it is brought in from main memory
     * @param[in] stats structure containing statistics for the simulation, necessary for any updates
     * @param[in] currTagL2 the calculated tag value for L2 cache
     * @param[in] currIndxL2 the calculated index for the L2 cache
     * @param[in] cacheHier structure containing linked lists for each cache level in the hierarchy
     * @param[in] addr the current full address, used when placing item in victim cache
     * @returns EXIT_SUCCESS or EXIT_FAILURE
     */
    int L2miss(performance *stats, memInfo *cacheCnfg, ulli currTagL2, ulli currIndxL2, allCache *cacheHier, ulli addr);

#endif // L2_CACHE_H
