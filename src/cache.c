/**
 * @file        cache.c
 * @authors     Rane Brown & Brian Douglass
 * @date        04-01-2016
 * @brief       Functions shared between cache levels
 *
 * index - a block "line"
 * tag - specific address in a block
 * offset - which byte in the block e.g. a 32 byte block would need 5 bits 2^5 to represent each byte
 * ways - number of chunks the cache is broken into
 * set  - the set of "ways" for a specific block
 */

#include "cache.h"

int calcBits(memInfo *mem, int *bitsIndexL1, int *bitsTagL1, int *bitsIndexL2, int *bitsTagL2)
{
    if(mem == NULL || bitsIndexL1 == NULL || bitsTagL1 == NULL || bitsIndexL2 == NULL || bitsTagL2 == NULL);
        return EXIT_FAILURE;

    // number of index bits L1 cache
    *bitsIndexL1 = log2((mem->L1dSize / mem->L1dBlock) / mem->L1dWays);

    // number of tag bits L1 cache
    *bitsTagL1 = log2(64 - *bitsIndexL1 - L1_OFFSET);

    // number of index bits L2 cache
    *bitsIndexL2 = log2((mem->L2Size / mem->L2Block) / mem->L2Ways);

    // number of tag bits L2 cache
    *bitsTagL2 = log2(64 - *bitsIndexL2 - L2_OFFSET);

    return EXIT_SUCCESS;
}
