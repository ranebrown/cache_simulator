
#include "config.h"

memInfo cache;

int main (int argc, char ** argv)
{
    FILE *config;
    char inStr[8];
    int i=0;

    (argc == 2) ? (config = fopen(argv[1],"r"))
                : (config = fopen("default.txt","r"));

    fscanf(config, "%s", inStr);
    printf("-- %s --\n",inStr);

    /* Copy the cache name minus the ".txt"
        This is a more reliable and safe way
        than using strncpy or strcpy. */
    while(argv[1][i] != '.')
    {
        printf("%c",argv[1][i]);
        cache.cacheName[i] = argv[1][i];
        i++;
    }
    printf("\nCache type: %s\n",cache.cacheName);
    setValues(inStr);

    return 0;
}

void setValues(char inStr[])
{
    /* L1 data */
    cache.L1dWays   = inStr[0]-'0';
    cache.L1dSize   = inStr[1]-'0';
    cache.L1dBlock  = 32;          // TODO

    /* L1 instruction */
    cache.L1iWays   = inStr[2]-'0';
    cache.L1iSize   = inStr[3]-'0';
    cache.L1iBlock  = 32;          // TODO

    /* L2 */
    cache.L2Ways    = inStr[4]-'0';
    cache.L2Size    = (inStr[5]-'0')*10 + (inStr[6]-'0');
    cache.L2Block   = 64;      // TODO

    /* Main Memory (default values) */
    cache.addrsendT = 10;
    cache.readyT    = 50;
    cache.chunkT    = 15;
    cache.chunkS    = 8;
}

void printCacheInfo()
{
	return;
}
