


#include "cacheCode.h"

int main()
{
    //int **L1i = NULL;
    memInfo *cacheCnfg = (memInfo *) malloc(sizeof(memInfo));
    cacheList *list    = (cacheList *) malloc(sizeof(cacheList));

    strcpy(cacheCnfg->cacheName,"default.txt");
    cacheCnfg->L1dBlock  = 32;
    cacheCnfg->L1iBlock  = 32;
    cacheCnfg->L2Block   = 64;

    /* L1 data */
    cacheCnfg->L1dWays   = 1;
    cacheCnfg->L1dSize   = 8192;
    cacheCnfg->L1dBlock  = 32;

    /* L1 instruction */
    cacheCnfg->L1iWays   = 1;
    cacheCnfg->L1iSize   = 8192;
    cacheCnfg->L1iBlock  = 32;

    /* L2 */
    cacheCnfg->L2Ways    = 1;
    cacheCnfg->L2Size    = 32768;
    cacheCnfg->L2Block   = 64;


    if( cacheInit(list, cacheCnfg) )
    {
        printf("init failed.\n");
    }

    list->L1i[200][3] = 100;
    printf("between functions %d\n",list->L1i[200][3]);

    deleteCache(list, cacheCnfg);

    free(cacheCnfg);
    free(list);

    printf("done\n");

    while(1)
    ;
    return 0;
}
