
#include "config.h"

memInfo cache;

int main (int argc, char ** argv)
{

    /***** The following are required for the main function *****/
    /* If there is a file included, it is the config needed */
    if(argv[1])
        //This works a little more reliably than
        //strcpy for unknown string lengths
        for(int i=0; argv[1][i] != '\0'; i++)
            cache.cacheName[i] = argv[1][i];
    /* Otherwise use the default values */
    else
        strcpy(cache.cacheName,"default.txt");

    printf("\nCache name: %s\n",cache.cacheName);

    if( setCacheValues() )
        printf("Error setting values.\n");

    return 0;
}

int setCacheValues ()
{
    FILE *config;
    char inStr[8];

    /* Open the file */
    if( !(config = fopen(cache.cacheName,"r")) )
    {
        printf("error opening file.\n");
        return 1;
    }

    /* Get the line from the file */
    fscanf(config, "%s", inStr);
    printf("-- %s --\n",inStr);

    /* Close the file */
    fclose(config);

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

    /* Check for fully associative */
    if(cache.L1dWays == 0)
    {
        printf("Fully Associative.\n");
    }

    /* Main Memory (default values) */
    cache.addrsendT = 10;
    cache.readyT    = 50;
    cache.chunkT    = 15;
    cache.chunkS    = 8;

    return 0;
}
