/**
 * @file        cacheCode.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Contains functions to implement the cache.
 */

#include "cacheCode.h"

int **cacheInit( memInfo *cacheCnfg)
{
    int lines = 0;
    int **newcache = NULL;


    printf("L1iWays: %d\nL1iSize: %d\nL1iBlock:%d\n",cacheCnfg->L1iWays, cacheCnfg->L1iSize, cacheCnfg->L1iBlock);

    /* Get the number of lines in the cache */
    lines = (int) (cacheCnfg->L1iSize/cacheCnfg->L1iBlock);
    printf("lines=%d\n",lines);

    /* Create the lines of the cache */
    newcache = (int**) calloc(lines,sizeof(int*));

    if(newcache) printf("Ok 1 newcache\n");

    for(int i=0; i<lines; i++)
    {
        newcache[i] = (int*) calloc(sizeof(cacheCnfg->L1iBlock)+2 , sizeof(int));//+tag);
        //if(newcache[i]) printf("Ok 2-%d newcache[%p]\n",i,newcache[i]);
    }


    //printf("L1dWays: %d\nL1dSize: %d\n",cacheCnfg->L1dWays,cacheCnfg->L1dSize);
    //printf("L2Ways:  %d\nL2Size:  %d\n",cacheCnfg->L2Ways,cacheCnfg->L2Size);

    return newcache;

}


int deleteCache(int **killedcache, memInfo *cacheCnfg)
{
    int lines = cacheCnfg->L1iSize/cacheCnfg->L1iBlock;
    for(int i=lines-1; i>=0; i--)
    {
        printf("%d\n",i);
        free(killedcache[i]);

    }

    free(killedcache);
    return 0;
}
