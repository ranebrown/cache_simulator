/**
 * @file        cacheCode.h
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Header file with function prototypes for the cache.
 */

#ifndef CACHE_H
    #define CACHE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "config.h"
    //#include "readTrace.h"


    typedef struct{
        int **L1i;
        int **L1d;
        int **L2;
        int **victim;
    }cacheList;

    /**
     * @brief builds all of the caches listed in cacheList
     * @param[in] cacheList - Struct of pointers to all caches
     * @param[in] memInfo - Struct of all cache configuration data
     * @param[out] cacheList - With fully built caches
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */

    int cacheInit(cacheList *, memInfo *);

    /**
     * @brief deletes all caches listed in cacheList
     * @param[in] cacheList - Struct of pointers to all caches.
     * @param[in] memInfo - Struct of all cache configuration data
     */
    void deleteCache(cacheList *, memInfo *);




#endif
