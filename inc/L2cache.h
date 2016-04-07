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

    #define L2OFFSET 6  ///< L2 is 64 bytes i.e. 2^6

    /**
     * @brief check reference is a hit or a miss
     * @param[in] addr address being checked
     * @return 0 hit, 1 miss
     */
    int checkL2(ulli addr);

    /**
     * @brief insert a new value into L2 cache
     * @param[in] addr address being inserted
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int insertL2(ulli addr);

#endif // L2_CACHE_H
