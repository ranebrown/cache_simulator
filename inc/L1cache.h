/**
 * @file        L1cache.h
 * @authors     Rane Brown & Brian Douglass
 * @date        04-06-2016
 * @brief       Function prototypes for the L1 cache
 */

#ifndef L1_CACHE_H
    #define L1_CACHE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include "L2cache.h"
    #include "cache.h"
    #include "common.h"

    /**
     * @brief check if instruction reference is a hit or a miss
     * @param[in] currIndx the index for block to check
     * @param[in] currTag the tag to be checked for
     * @param[in] cacheHier pointer to strucute holding the caches
     * @return 0 hit, 1 miss, EXIT_FAILURE any other error
     */
    int checkL1i(ui currIndx, ulli currTag, allCache *cacheHier);

    /**
     * @brief check if data read reference is a hit or a miss
     * @param[in] currIndx the index for block to check
     * @param[in] currTag the tag to be checked for
     * @param[in] cacheHier pointer to strucute holding the caches
     * @return 0 hit, 1 miss EXIT_FAILURE any other error
     */
    int checkL1dR(ui currIndx, ulli currTag, allCache *cacheHier);

    /**
     * @brief check if data write reference is a hit or a miss, sets dirty bit if hit occurs
     * @param[in] currIndx the index for block to check
     * @param[in] currTag the tag to be checked for
     * @param[in] cacheHier pointer to strucute holding the caches
     * @return 0 hit, 1 miss EXIT_FAILURE any other error
     */
    int checkL1dW(ui currIndx, ulli currTag, allCache *cacheHier);

    /**
     * @brief upon a miss in the L1 instruction cache this function is called
     *
     * First the L1i victim cache is checked and if the desired value is found then it is moved into the L1i cache.
     * If the desired value is not found in the victim cache then the function calls an additional function to check the L2 cache.
     * If misses continue to occure in each cache level the desired value will eventually be brought in from main memory.
     * This Function returns EXIT_SUCCESS upon successful completion which indicates there was a hit in one of the cache levels
     * or the value was brought in from main memory. It will return EXIT_FAILURE if there is a problem at any memory level.
     *
     * @param[in] stats structure containing statistics for the simulation, necessary for any updates
     * @param[in] cacheCnfg structure containing cache configuration parameters
     * @param[in] currTagL1 the calcualted tag value for L1 cache
     * @param[in] currTagL2 the calculated tag value for L2 cache
     * @param[in] currIndxL1 the calculated index for L1 cache
     * @param[in] currIndxL2 the calculated index for the L2 cache
     * @param[in] cacheHier structure containing linked lists for each cache level in the hierarchy
     * @param[in] addr the current full address, used when placing item in victim cache
     * @returns EXIT_SUCCESS or EXIT_FAILURE
     */
    int L1iMiss(performance *stats, memInfo* cacheCnfg, ulli currTagL1, ulli currTagL2, int currIndxL1, int currIndxL2, allCache *cacheHier, ulli addr);

    /**
     * @brief upon a miss in the L1 data cache this function is called
     * @param[in] stats structure containing statistics for the simulation, necessary for any updates
     * @param[in] cacheCnfg structure containing cache configuration parameters
     * @param[in] currTagL1 the calcualted tag value for L1 cache
     * @param[in] currTagL2 the calculated tag value for L2 cache
     * @param[in] currIndxL1 the calculated index for L1 cache
     * @param[in] currIndxL2 the calculated index for the L2 cache
     * @param[in] cacheHier structure containing linked lists for each cache level in the hierarchy
     * @param[in] addr the current full address, used when placing item in victim cache
     * @param[in] rw determines if request is a read or write 0 = read, 1 = write
     * @returns EXIT_SUCCESS or EXIT_FAILURE
     */
    int L1dMiss(performance *stats, memInfo* cacheCnfg,  ulli currTagL1, ulli currTagL2, int currIndxL1, int currIndxL2,
                allCache *cacheHier, ulli addr, int rw);

#endif // L1_CACHE_H
