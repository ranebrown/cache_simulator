/**
 * @file        cache.c
 * @authors     Rane Brown & Brian Douglass
 * @date        04-01-2016
 * @brief       Functions shared between cache levels
 */

/*
 *
 * each address is broken down into msb - |tag|index|block offset| -  lsb
 * index: which set to select, middle bits of address
 * tag: which block in the set, the upper bits of address
 * offset: which byte in the block e.g. a 32 byte block would need 5 bits 2^5 to represent each byte
 *
 * Each degree of associativity decreases the number of sets by a factor of
 * 2 and thus decreases the number of bits used to index the cache by 1 and
 * increases the number of bits in the tag by 1
 *
 * ways - number of chunks the cache is broken into
 * set  - the set of "ways" for a specific block
 *
 * # of offset bits = log2(byte size of cache)
 * # of index bits = log2(# of blocks in the cache)
 * # of tags bits = total address bits - # index bits - # offset bits
 *
 * index = (address << # tag bits ) >> (#tag bits + offset)
 * tag = address >> (# index bits + offset)
 *
 */
#include "cache.h"

int L1(char op, unsigned long long int addr, unsigned int numBytes, block **l1cache, memInfo *mem)
{
    // index and tag variables
    int currIndx = 0;
    ulli currTag = 0;

    // calculate the word aligned start address
    ulli currAddr = addr & 0xFFFFFFFFFFFFFFFC;

    // calculate the word aligned end address
    ulli endAddr = (addr + numBytes) & 0xFFFFFFFFFFFFFFFC;

    // TODO check for type of op -> create different functions for each

    while(currAddr <= endAddr)
    {
        // calculate the index and tag for the current address
        // TODO can use log2() for this calculation?
        currIndx = (currAddr / mem->L1dBlock) % (mem->L1dSize / mem->L1dBlock);
        currTag = currAddr >> (64 - ((int)log2(mem->L1dSize / mem->L1dBlock) + (int)log2(mem->L1dBlock)));

        // check if the current tag is in the cache
        if( (l1cache[currIndx]->tag == currTag) && (l1cache[currIndx]->valid == 1) )
        {
            // hit
            // TODO stats
        }
        else
        {
            // TODO check victim cache
            // TODO check L2 cache
        }

        // increment address 4 bytes
        currAddr += 4;
    }
    return EXIT_SUCCESS;
}
