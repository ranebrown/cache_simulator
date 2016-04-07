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

    #define L1OFFSET 5  ///< L1 is 32 bytes i.e. 2^5

    /**
     * @brief check if instruction reference is a hit or a miss
     * @param[in] addr address being checked
     * @return 0 hit, 1 miss
     */
    int checkL1i(ulli addr);

    /**
     * @brief check if data read/write reference is a hit or a miss
     * @param[in] addr address being checked
     * @return 0 hit, 1 miss
     */
    int checkL1d(ulli addr);

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
