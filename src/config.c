/**
 * @file        config.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Contains functions defined in the config.h header file.
 */
#include "config.h"

/* #define PRINTVALUES         ///< print statements for debugging */

int setCacheValues (memInfo *cacheCnfg)
{
    /* Local variables */
    FILE *config;
    int temp1=0, temp2=0, temp3=0;

    /* Open the file */
    if( !(config = fopen(cacheCnfg->cacheName,"r")) )
        PERR("error opening file");

    /* Read the line from the file */
    fscanf(config, "%d %d %d %d %d %d", &(cacheCnfg->L1dWays), &temp1, \
                                        &(cacheCnfg->L1iWays), &temp2, \
                                        &(cacheCnfg->L2Ways),  &temp3);

    /* Close the file */
    if( fclose(config) )
        PERR("error closing file");

    cacheCnfg->L1dSize = pow(2,temp1);
    cacheCnfg->L1iSize = pow(2,temp2);
    cacheCnfg->L2Size  = pow(2,temp3);

    return EXIT_SUCCESS;
}

int calculateCost(memInfo *cacheCnfg)
{
    int numWaysL1,numWaysL2;

#ifdef PRINTVALUES
    printf("CACHE NAME: %s\n",cacheCnfg->cacheName);
    printf("L1dWays: %d\nL1dSize: %d\n",  cacheCnfg->L1dWays,cacheCnfg->L1dSize);
    printf("L1iWays: %d\nL1iSize: %d\n",  cacheCnfg->L1iWays,cacheCnfg->L1iSize);
    printf("L2Ways:  %d\nL2Size:  %d\n\n",cacheCnfg->L2Ways,cacheCnfg->L2Size);
#endif

    cacheCnfg->memoryCost = 75 + BW_COST*TIMES_BW_DBL;

    /* If either the L1 or L2 is fully associative calculate their costs separatly */
    if(cacheCnfg->L1iWays == 0)
    {
        numWaysL1 = cacheCnfg->L1dSize / cacheCnfg->L1dBlock;

        /* Get the cost of the L1i and L1d caches */
        cacheCnfg->L1dCost   = (L1_4KB * cacheCnfg->L1dSize/4096) +
                               (L1_ASSOC * log2(numWaysL1) * cacheCnfg->L1dSize/4096);
        cacheCnfg->L1iCost   = (L1_4KB * cacheCnfg->L1iSize/4096) +
                               (L1_ASSOC * log2(numWaysL1) * cacheCnfg->L1iSize/4096);
        cacheCnfg->L1TotCost = cacheCnfg->L1dCost + cacheCnfg->L1iCost;
    }
    if(cacheCnfg->L2Ways == 0)
    {
        numWaysL2 = cacheCnfg->L2Size / cacheCnfg->L2Block;

        /* Get the L2 cache cost */
        cacheCnfg->L2Cost    = (L2_16KB * cacheCnfg->L2Size/16384) +
                               (L2_ASSOC * log2(numWaysL2) * cacheCnfg->L2Size/16384);
        cacheCnfg->totalCost = cacheCnfg->L1TotCost + cacheCnfg->L2Cost + cacheCnfg->memoryCost;
    }
    if(cacheCnfg->L1iWays != 0 && cacheCnfg->L2Ways != 0)
    {
        /* Get the cost of the L1i and L1d caches */
        cacheCnfg->L1dCost   = (L1_4KB * cacheCnfg->L1dSize/4096) +
                               (L1_ASSOC * log2(cacheCnfg->L1dWays) * cacheCnfg->L1dSize/4096);
        cacheCnfg->L1iCost   = (L1_4KB * cacheCnfg->L1iSize/4096) +
                               (L1_ASSOC * log2(cacheCnfg->L1iWays) * cacheCnfg->L1iSize/4096);
        cacheCnfg->L1TotCost = cacheCnfg->L1dCost + cacheCnfg->L1iCost;

        /* Get the L2 cache cost */
        cacheCnfg->L2Cost    = (L2_16KB * cacheCnfg->L2Size/16384) + (L2_ASSOC * log2(cacheCnfg->L2Ways) * cacheCnfg->L2Size/16384);
        cacheCnfg->totalCost = cacheCnfg->L1TotCost + cacheCnfg->L2Cost + cacheCnfg->memoryCost;
    }

#ifdef PRINTVALUES
    printf("L1 cache cost (Icache $%d) + (Dcache $%d) = $%d\n", \
           cacheCnfg->L1iCost, cacheCnfg->L1dCost, cacheCnfg->L1TotCost);
    printf("L2 cache cost = $%d;  Memory cost = %d  Total cost = $%d\n", \
            cacheCnfg->L2Cost, cacheCnfg->memoryCost, cacheCnfg->totalCost);
#endif

    return 0;
}


char *getName(char *str)
{
    int i=0,j=0,k=0,l=0;
    int flag = 0; // 0=cacheName, 1=argv
    char temp[128];


    //Find the '.' in the '.txt' or '.gz'
    for(i=0;i<128;i++)
        if(str[i] == '.' && str[i+1] == 't')
        {
            flag = 0;
            break;
        }
        else if(str[i] == '.' && str[i+1] == 'g')
        {
            flag = 1;
            break;
        }

    //Find the '/' prior to the  name
    for(j=i;j>0;j--)
        if(str[j] == '/')
        {
            j++;
            break;
        }

    //Copy the string into the temp string
    for(k=j;k<i;k++)
        temp[l++] = str[k];

    //Copy temp the beginning of the name
    for(k=0;k<(i-j);k++)
        str[k] = temp[k];

    //Fill the unused part of the cacheName with '\0'
    for(i=k;k<128;k++)
        str[k] = '\0';

    return str;
}
