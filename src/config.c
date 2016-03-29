/**
 * @file        config.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Contains functions defined in the config.h header file.
 */
#include "config.h"

int setCacheValues (memInfo cache)
{
    FILE *config;
    char inStr[8];

    printf("About to open: %s\n",cache.cacheName);
    /* Open the file */
    if( !(config = fopen(cache.cacheName,"r")) )
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
    cache.L1dWays   = inStr[0]-'0';
    cache.L1dSize   = inStr[1]-'0';
    cache.L1dBlock  = 32;          // TODO Is this correct?

    /* L1 instruction */
    cache.L1iWays   = inStr[2]-'0';
    cache.L1iSize   = inStr[3]-'0';
    cache.L1iBlock  = 32;          // TODO Is this correct?

    /* L2 */
    cache.L2Ways    = inStr[4]-'0';
    cache.L2Size    = (inStr[5]-'0')*10 + (inStr[6]-'0');
    cache.L2Block   = 64;         // TODO Is this correct?

    #ifdef LISTVALUES
        /* Check for fully associative */
        if(cache.L1dWays == 0)
        {
            printf("Fully Associative.\n");
        }
    #endif

    /* Main Memory (default values) */
    cache.addrsendT = 10;
    cache.readyT    = 50;
    cache.chunkT    = 15;
    cache.chunkS    = 8;

    return EXIT_SUCCESS;
}

int calculateCost(memInfo cache)
{

    return 0;
}
