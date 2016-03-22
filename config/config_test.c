
#include "config.h"

memInfo cache;

int main (int argc, char ** argv)
{
    FILE *config;
    char inStr[11];

    (argc == 2) ? (config = fopen(argv[1],"r"))
                : (config = fopen("default","r"));

    fscanf(config, "%s", inStr);
    printf("-- %s --\n",inStr);

    setValues(inStr);

    //printf("string length: %lu\n",strlen(inStr));

    return 0;
}

void setValues(char inStr[])
{
    /* L1 data */
    cache.L1dType   = inStr[0]-'0';
    cache.L1dWays   = inStr[1]-'0';
    cache.L1dSize   = inStr[2]-'0';
    cache.L1dBlock  = 32;          // TODO

    /* L1 instruction */
    cache.L1iType   = inStr[3]-'0';
    cache.L1iWays   = inStr[4]-'0';
    printf("L1iWays: %d\n",cache.L1dType);
    cache.L1iSize   = inStr[5]-'0';
    cache.L1iBlock  = 32;          // TODO

    /* L2 */
    cache.L2Type    = inStr[6]-'0';
    cache.L2Ways    = inStr[7]-'0';
    cache.L2Size    = (inStr[8]-'0')*10 + (inStr[9]-'0');
    printf("L2 size: %d\n",cache.L2Size);
    cache.L2Block   = 64;      // TODO

    /* Main Memory */
    cache.addrsendT = 10;
    cache.readyT    = 50;
    cache.chunkT    = 15;
    cache.chunkS    = 8;
}
