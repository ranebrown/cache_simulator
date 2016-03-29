/**
 * @file        config.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Contains functions defined in the config.h header file.
 */
#include "config.h"

int setCacheValues (memInfo *cache)
{
    FILE *config;
    char inStr[8];

    printf("About to open: %s\n",cache->cacheName);
    /* Open the file */
    if( !(config = fopen(cache->cacheName,"r")) )
    {
        printf("Error opening file.\n");
        return EXIT_FAILURE;
    }

    /* Get the line from the file */
    fscanf(config, "%s", inStr);

    #ifdef LISTVALUES
        printf("Input string: ->%s<-\n",inStr);
    #endif

    /* Close the file */
    if( fclose(config) )
    {
        printf("Error closing file.\n");
        return EXIT_FAILURE;
    }

    /** Set the cache parameters from the file **/
    /* L1 data */
    cache->L1dWays   = inStr[0]-'0';
    cache->L1dSize   = inStr[1]-'0';
    cache->L1dBlock  = 32;          // TODO Is this correct?

    /* L1 instruction */
    cache->L1iWays   = inStr[2]-'0';
    cache->L1iSize   = inStr[3]-'0';
    cache->L1iBlock  = 32;          // TODO Is this correct?

    /* L2 */
    cache->L2Ways    = inStr[4]-'0';
    cache->L2Size    = (inStr[5]-'0')*10 + (inStr[6]-'0');
    cache->L2Block   = 64;         // TODO Is this correct?

    #ifdef LISTVALUES
        /* Check for fully associative */
        if(cache->L1dWays == 0)
        {
            printf("Fully Associative.\n");
        }
    #endif

    /* Main Memory (default values) */
    cache->addrsendT = 10;
    cache->readyT    = 50;
    cache->chunkT    = 15;
    cache->chunkS    = 8;

    return EXIT_SUCCESS;
}

int calculateCost(memInfo *cache)
{

    #ifdef LISTVALUES
        printf("L1dWays: %d\nL1dSize: %d\n",cache->L1dSize,cache->L1dSize);
        printf("L1iWays: %d\nL1iSize: %d\n",cache->L1iSize,cache->L1iSize);
    #endif
    cache->L1dCost = (int) (L1_4KB * cache->L1dSize / 4) + (L1_ASSOC * cache->L1dSize);
    printf("L1dCost: %d\n\n", cache->L1dCost);
    cache->L1iCost = (int) (L1_4KB * cache->L1iSize / 4) + (L1_ASSOC * cache->L1iSize);

    cache->L1TotCost = cache->L1dCost + cache->L1iCost;

    cache->L2Cost = (int) (L2_16KB * cache->L2Size / 16) + (L1_ASSOC * cache->L2Size);

    cache->totalCost = cache->L1TotCost + cache->L2Cost + cache->memoryCost;

    #ifdef LISTVALUES

    printf("L1 cache cost (Icache $%d) + (Dcache $%d) = $%d\n", \
           cache->L1iCost, cache->L1dCost, cache->L1TotCost);
    printf("L2 cache cost = $%d;  Memory cost = %d  Total cost = %d\n", \
            cache->L2Cost, cache->memoryCost, cache->totalCost);

    #endif
    return 0;
}















//placeholder
