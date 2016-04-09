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
    #include "cache.h"

    /**
     * @brief check if instruction reference is a hit or a miss
     * @param[in] currIndx the index for block to check
     * @param[in] currTag the tag to be checked for
     * @return 0 hit, 1 miss
     */
    int checkL1i(ui currIndx, ulli currTag);

    /**
     * @brief check if data read/write reference is a hit or a miss
     * @param[in] currIndx the index for block to check
     * @param[in] currTag the tag to be checked for
     * @return 0 hit, 1 miss
     */
    int checkL1d(ui currIndx, ulli currTag);

    int L1iMiss(ulli currTagL1, ulli currTagL2, int currIndxL1, int currIndxL2);
    int L1dMiss(ulli currTagL1, ulli currTagL2, int currIndxL1, int currIndxL2, int dirtyBit);
    int L1dMiss(ulli currTagL1, ulli currTagL2, int currIndxL1, int currIndxL2, int dirtyBit);

    /**
     * @brief insert a new value into L1 instruction cache
     * @param[in] addr address being inserted
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int insertL1i(ulli addr);

    /**
     * @brief insert a new value into L1 data cache
     * @param[in] addr address being inserted
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int insertL1d(ulli addr);

#endif // L1_CACHE_H
