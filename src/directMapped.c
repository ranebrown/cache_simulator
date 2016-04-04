/**
 * @file        directMapped.c
 * @authors     Rane Brown & Brian Douglass
 * @date        04-01-2016
 * @brief       Functions related to a direct mapped cache
 */

#include "directMapped.h"

int L1(char op, unsigned long long int addr, unsigned int numBytes, block *L1, memInfo *mem)
{
    // index and tag variables
    int currIndx = 0;
    unsigned long long currTag = 0;

    // calculate the word aligned start address
    unsigned long long startAddr = addr & 0xFFFFFFFFFFFFFFFC;

    // calculate the word aligned end address
    unsigned long long endAddr = (addr + numBytes) & 0xFFFFFFFFFFFFFFFC;

    // TODO check for type of op -> create different functions for each

    while(startAddr <= endAddr)
    {
        // calculate the index and tag for the current address
        // TODO can use log2() for this calculation?
        currIndx = (currAddr / mem->L1dBlock) % (mem->L1dSize / mem->L1dBlock);
        currTag = currAddr >> (64 - (log2(mem->l1dSize / mem->L1dBlock) + log2(mem->L1dBlock)));

        // check if the current tag is in the cache
        if( (L1[currIndx]->tag == currTag) && (L1[currIndx]->valid == 1) )
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
        startAddr += 4;
    }
}
