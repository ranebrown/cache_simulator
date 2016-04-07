/**
 * @file        cacheCode.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Contains functions to implement the cache.
 */

#include "cacheCode.h"

int cacheInit(cacheList *list, memInfo *cacheCnfg)
{
    int lines = 0;


    /********** Create the L1 instruction cache **********/
    /* Get the number of lines in the cache */
    lines = (int) (cacheCnfg->L1iSize/cacheCnfg->L1iBlock);
    printf("L1i lines=%d\n",lines);

    /* Create the lines of the cache */
    list->L1i = (int**) calloc(lines,sizeof(int*));

    if(list->L1i) printf("Ok L1i\n");

    for(int i=0; i<lines; i++)
    {
        list->L1i[i] = (int*) calloc(sizeof(cacheCnfg->L1iBlock)+2 , sizeof(int));//+tag);
    }


    /********** Create the L1 data cache **********/
    /* Get the number of lines in the cache */
    lines = (int) (cacheCnfg->L1dSize/cacheCnfg->L1dBlock);
    printf("Lid lines=%d\n",lines);

    /* Create the lines of the cache */
    list->L1d = (int**) calloc(lines,sizeof(int*));

    if(list->L1d) printf("Ok L1d\n");

    for(int i=0; i<lines; i++)
    {
        list->L1d[i] = (int*) calloc(sizeof(cacheCnfg->L1dBlock)+2 , sizeof(int));//+tag);
    }

    /********** Create the L2 cache **********/
    /* Get the number of lines in the cache */
    lines = (int) (cacheCnfg->L2Size/cacheCnfg->L2Block);
    printf("L2 lines=%d\n",lines);

    /* Create the lines of the cache */
    list->L2 = (int**) calloc(lines,sizeof(int*));

    if( !(list->L1i) ) printf("Ok L2\n");

    for(int i=0; i<lines; i++)
    {
        list->L2[i] = (int*) calloc(sizeof(cacheCnfg->L2Block)+2 , sizeof(int));//+tag);
    }

    //printf("L1iWays: %d\nL1iSize: %d\nL1iBlock:%d\n",cacheCnfg->L1iWays, cacheCnfg->L1iSize, cacheCnfg->L1iBlock);
    //printf("L1dWays: %d\nL1dSize: %d\n",cacheCnfg->L1dWays,cacheCnfg->L1dSize);
    //printf("L2Ways:  %d\nL2Size:  %d\n",cacheCnfg->L2Ways,cacheCnfg->L2Size);

    return EXIT_SUCCESS;
}


void deleteCache(cacheList *list, memInfo *cacheCnfg)
{
    int lines = cacheCnfg->L1iSize/cacheCnfg->L1iBlock;
    for(int i=lines-1; i>=0; i--)
        free(list->L1i[i]);
    free(list->L1i);

    lines = cacheCnfg->L1dSize/cacheCnfg->L1dBlock;
    for(int i=lines-1; i>=0; i--)
        free(list->L1d[i]);
    free(list->L1d);

    lines = cacheCnfg->L2Size/cacheCnfg->L2Block;
    for(int i=lines-1; i>=0; i--)
        free(list->L2[i]);
    free(list->L2);

    /*
    lines = cacheCnfg->vSize/cacheCnfg->vBlock;
    for(int i=lines-1; i>=0; i--)
        free(list->victim[i]);
    free(list->victim);
    */
}























//placeholder
