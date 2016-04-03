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

    int **cacheInit( memInfo *);

    int deleteCache(int **, memInfo *);




#endif
