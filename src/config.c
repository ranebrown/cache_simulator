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
    //TODO Add functionality for fully associative cache

    // #ifdef LISTVALUES
    //     printf("L1dWays: %d\nL1dSize: %d\n",cache->L1dWays,cache->L1dSize);
    //     printf("L1iWays: %d\nL1iSize: %d\n",cache->L1iWays,cache->L1iSize);
    //     printf("L2Ways:  %d\nL2Size:  %d\n",cache->L2Ways,cache->L2Size);
    // #endif

    cache->memoryCost = 75;

    /* Get the cost of the L1i and L1d caches */
    // $100 for every 4KB, L1 cache
    if(cache->L1dSize == 4)
    {
        cache->L1dCost = 100;
        cache->L1iCost = 100;
        printf("L1d == 4\n");
    }
    else //8KB
    {
        cache->L1dCost = 200;
        cache->L1iCost = 200;
        printf("L1d == 8\n");
    }
    // An additional $100 every time the ways are doubled, L1 cache
    if(cache->L1iWays == 2)
    {
        cache->L1dCost += 100;
        cache->L1iCost += 100;
        printf("L1 ways == 2\n");
    }
    else if(cache->L1iWays == 4)
    {
        cache->L1dCost += 200;
        cache->L1iCost += 200;
        printf("L1 ways == 4\n");
    }
    else if(cache->L1iWays == 8)
    {
        cache->L1dCost += 400;
        cache->L1iCost += 400;
        printf("L1 ways == 8\n");
    }
    // else
    // {
    //     cache->L1dCost += 100;
    //     cache->L1iCost += 100;
    // }
    // TODO FULLY ASSOCIATIVE
    // else if(cache->L1iWays == FULLY ASSOCIATIVE)
    // {
    //     cache-L1Cost += COST;
    // }
    cache->L1TotCost = cache->L1dCost + cache->L1iCost;


    if(cache->L2Size == 16)
    {
        cache->L2Cost = 50;
    }
    else
    {
        cache->L2Cost = 100;
    }

    if(cache->L2Ways == 2)
    {
        cache->L2Cost += 100;
    }
    else if(cache->L2Ways == 4)
    {
        cache->L2Cost += 150;
    }
    cache->totalCost = cache->L1TotCost + cache->L2Cost + cache->memoryCost;

    // TODO extra simulation using sjeng trace with different parameters.


    #ifdef LISTVALUES
    printf("L1 cache cost (Icache $%d) + (Dcache $%d) = $%d\n", \
           cache->L1iCost, cache->L1dCost, cache->L1TotCost);
    printf("L2 cache cost = $%d;  Memory cost = %d  Total cost = $%d\n", \
            cache->L2Cost, cache->memoryCost, cache->totalCost);
    #endif


    return 0;
}

/*
printf("i=%d\n",i);
// Get divisor i in order to
while(temp)
{
    temp /= 4;
    i++;
    printf("i=%d temp = %d\n",i,temp);
}
i--;
printf("final i=%d\nwaysDoubled=%d",i,waysDoubled);
cache->L1dCost   = (int) ((L1_4KB * cache->L1dSize / i) + (L1_ASSOC * waysDoubled));
cache->L1iCost   = (int) ((L1_4KB * cache->L1iSize / i) + (L1_ASSOC * waysDoubled));
cache->L1TotCost = cache->L1dCost + cache->L1iCost;


while(temp1)
{
    temp1 /= 16;
    j++;
}
waysDoubled = log2(cache->L1dWays);
if(!waysDoubled)
{
    waysDoubled = 1;
}
cache->L2Cost    = (int) ((L2_16KB * cache->L2Size / j) + (L1_ASSOC * waysDoubled));

*/











//placeholder
