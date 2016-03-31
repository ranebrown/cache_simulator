/**
 * @file        config.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Contains functions defined in the config.h header file.
 */
#include "config.h"

int setCacheValues (memInfo *cache)
{
    /* Local variables */
    FILE *config;
    int temp;
    char inStr[10];

    #ifdef PRINTVALUES
        printf("About to open: %s\n",cache->cacheName);
    #endif

    /* Open the file */
    if( !(config = fopen(cache->cacheName,"r")) )
    {
        printf("Error opening file.\n");
        return EXIT_FAILURE;
    }

    /* Read the line from the file */
    fscanf(config, "%s", inStr);

    #ifdef PRINTVALUES
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
    temp             = (inStr[1]-'0')*10 + (inStr[2]-'0');
    cache->L1dSize   = pow(2,temp);
    cache->L1dBlock  = 32;          // TODO Is this correct?

    /* L1 instruction */
    cache->L1iWays   = inStr[3]-'0';
    temp             = (inStr[4]-'0')*10 + (inStr[5]-'0');
    cache->L1iSize   = pow(2,temp);
    cache->L1iBlock  = 32;          // TODO Is this correct?

    /* L2 */
    cache->L2Ways    = inStr[6]-'0';
    temp             = (inStr[7]-'0')*10 + (inStr[8]-'0');
    cache->L2Size    = pow(2,temp);
    cache->L2Block   = 64;         // TODO Is this correct?

    #ifdef PRINTVALUES
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
    //TODO Add functionality for fully associative cache

    #ifdef PRINTVALUES
        printf("L1dWays: %d\nL1dSize: %d\n",cache->L1dWays,cache->L1dSize);
        printf("L1iWays: %d\nL1iSize: %d\n",cache->L1iWays,cache->L1iSize);
        printf("L2Ways:  %d\nL2Size:  %d\n",cache->L2Ways,cache->L2Size);
    #endif

    cache->memoryCost = 75;

    /* Get the cost of the L1i and L1d caches */
    cache->L1dCost   = (L1_4KB * cache->L1dSize/4096) + (L1_ASSOC * log2(cache->L1dWays) * cache->L1dSize/4096);
    cache->L1iCost   = (L1_4KB * cache->L1iSize/4096) + (L1_ASSOC * log2(cache->L1iWays) * cache->L1iSize/4096);
    cache->L1TotCost = cache->L1dCost + cache->L1iCost;

    /* Get the L2 cache cost */
    cache->L2Cost    = (L2_16KB * cache->L2Size/16384) + (L2_ASSOC * log2(cache->L2Ways) * cache->L2Size/16384);


    cache->totalCost = cache->L1TotCost + cache->L2Cost + cache->memoryCost;

    // TODO extra simulation cost using sjeng trace with different parameters.


    #ifdef PRINTVALUES
    printf("L1 cache cost (Icache $%d) + (Dcache $%d) = $%d\n", \
           cache->L1iCost, cache->L1dCost, cache->L1TotCost);
    printf("L2 cache cost = $%d;  Memory cost = %d  Total cost = $%d\n", \
            cache->L2Cost, cache->memoryCost, cache->totalCost);
    #endif


    return 0;
}

int ilog2(int x)
{
    int y = 0;
    while(x >>= 1) ++y;
    return y;
}








//placeholder
