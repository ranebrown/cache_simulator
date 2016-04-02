/**
 * @file        config.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Contains functions defined in the config.h header file.
 */
#include "config.h"

int setCacheValues (memInfo *cacheCnfg)
{
    /* Local variables */
    FILE *config;
    int temp;
    char inStr[10];

    #ifdef PRINTVALUES
        printf("About to open: %s\n",cacheCnfg->cacheName);
    #endif

    /* Open the file */
    if( !(config = fopen(cacheCnfg->cacheName,"r")) )
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
    cacheCnfg->L1dWays   = inStr[0]-'0';
    temp             = (inStr[1]-'0')*10 + (inStr[2]-'0');
    cacheCnfg->L1dSize   = pow(2,temp);

    /* L1 instruction */
    cacheCnfg->L1iWays   = inStr[3]-'0';
    temp             = (inStr[4]-'0')*10 + (inStr[5]-'0');
    cacheCnfg->L1iSize   = pow(2,temp);

    /* L2 */
    cacheCnfg->L2Ways    = inStr[6]-'0';
    temp             = (inStr[7]-'0')*10 + (inStr[8]-'0');
    cacheCnfg->L2Size    = pow(2,temp);

    #ifdef PRINTVALUES
        /* Check for fully associative */
        if(cacheCnfg->L1dWays == 0)
        {
            printf("Fully Associative.\n");
        }
    #endif



    return EXIT_SUCCESS;
}

int calculateCost(memInfo *cacheCnfg)
{
    //TODO Add functionality for fully associative cache

    #ifdef PRINTVALUES
        printf("L1dWays: %d\nL1dSize: %d\n",cacheCnfg->L1dWays,cacheCnfg->L1dSize);
        printf("L1iWays: %d\nL1iSize: %d\n",cacheCnfg->L1iWays,cacheCnfg->L1iSize);
        printf("L2Ways:  %d\nL2Size:  %d\n",cacheCnfg->L2Ways,cacheCnfg->L2Size);
    #endif

    cacheCnfg->memoryCost = 75;

    /* Get the cost of the L1i and L1d caches */
    cacheCnfg->L1dCost   = (L1_4KB * cacheCnfg->L1dSize/4096) + (L1_ASSOC * log2(cacheCnfg->L1dWays) * cacheCnfg->L1dSize/4096);
    cacheCnfg->L1iCost   = (L1_4KB * cacheCnfg->L1iSize/4096) + (L1_ASSOC * log2(cacheCnfg->L1iWays) * cacheCnfg->L1iSize/4096);
    cacheCnfg->L1TotCost = cacheCnfg->L1dCost + cacheCnfg->L1iCost;

    /* Get the L2 cache cost */
    cacheCnfg->L2Cost    = (L2_16KB * cacheCnfg->L2Size/16384) + (L2_ASSOC * log2(cacheCnfg->L2Ways) * cacheCnfg->L2Size/16384);


    cacheCnfg->totalCost = cacheCnfg->L1TotCost + cacheCnfg->L2Cost + cacheCnfg->memoryCost;

    // TODO extra simulation cost using sjeng trace with different parameters.


    #ifdef PRINTVALUES
    printf("L1 cache cost (Icache $%d) + (Dcache $%d) = $%d\n", \
           cacheCnfg->L1iCost, cacheCnfg->L1dCost, cacheCnfg->L1TotCost);
    printf("L2 cache cost = $%d;  Memory cost = %d  Total cost = $%d\n", \
            cacheCnfg->L2Cost, cacheCnfg->memoryCost, cacheCnfg->totalCost);
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
