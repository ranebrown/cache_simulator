/**
 * @file        L1cache.c
 * @authors     Rane Brown & Brian Douglass
 * @date        04-06-2016
 * @brief       Function for the L1 cache
 */

#include "L1cache.h"

int checkL1i(ui currIndx, ulli currTag, allCache *cacheHier)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
    {
        fprintf(stderr,"ERROR: cache not initialized in %s function: %s: line %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    /* get the first block in the list */
    node *tmpNode = cacheHier->L1i[currIndx]->first;

    /* check each way for a hit */
    while(tmpNode != NULL)
    {
        if(tmpNode->valid && tmpNode->tag == currTag)
        {
            // move node to first way (LRU policy)
            if(bumpToFirst(cacheHier->L1i[currIndx], currTag) != 0)
            {
                fprintf(stderr,"ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            return HIT;
        }
        else
            tmpNode = tmpNode->next;
    }
    return MISS;
}

int checkL1dR(ui currIndx, ulli currTag, allCache *cacheHier)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
    {
        fprintf(stderr,"ERROR: cache not initialized in %s function: %s: line %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    /* get the first block in the list */
    node *tmpNode = cacheHier->L1d[currIndx]->first;

    /* check each way for a hit */
    while(tmpNode != NULL)
    {
        if(tmpNode->valid && tmpNode->tag == currTag)
        {
            // move node to first way (LRU policy)
            if(bumpToFirst(cacheHier->L1d[currIndx], currTag) != 0)
            {
                fprintf(stderr,"ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            return HIT;
        }

        else
            tmpNode = tmpNode->next;
    }
    return MISS;
}

int checkL1dW(ui currIndx, ulli currTag, allCache *cacheHier)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
    {
        fprintf(stderr,"ERROR: cache not initialized in %s function: %s: line %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    /* get the first block in the list */
    node *tmpNode = cacheHier->L1d[currIndx]->first;

    /* check each way for a hit */
    while(tmpNode != NULL)
    {
        if(tmpNode->valid && tmpNode->tag == currTag)
        {
            // mark block as dirty
            tmpNode->dirty = DIRTY;

            // move node to first way (LRU policy)
           if(bumpToFirst(cacheHier->L1d[currIndx], currTag) != 0)
           {
               fprintf(stderr,"ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
               return EXIT_FAILURE;
           }

            return HIT;
        }
        else
            tmpNode = tmpNode->next;
    }
    return MISS;
}

int L1iMiss(performance *stats, ulli currTagL1, ulli currTagL2, int currIndxL1, int currIndxL2, allCache *cacheHier)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
    {
        fprintf(stderr,"ERROR: cache not initialized in %s function: %s: line %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    /* get the first entry in the L1 victim cache */
    node *VCL1iNode = cacheHier->VCL1i->first;

    /* get the node from the L1 cache */
    node *L1iNode = cacheHier->L1i[currIndxL1]->first;

    // search victim cache for the tag
    while(VCL1iNode != NULL)
    {
        // the enty was found in the L1i victim cache
        if(VCL1iNode->valid && VCL1iNode->tag == currTagL1)
        {
            // move found entry to front of list (LRU policy)
            if(bumpToFirst(cacheHier->VCL1i, currTagL1) != 0)
            {
                fprintf(stderr,"ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            // reset VCL1iNode to its new location
            VCL1iNode = cacheHier->VCL1i->first;

            // increment statistics for simulation
            stats->cycleInst += L1_HIT_T; // VC to L1 same time as an L1 hit
            stats->VChitL1i++;
            stats->transfersL1i++;

            // check if there is a way that is not valid
            while(L1iNode != NULL)
            {
                // there is a way in L1i that is not valid -> write directly to it, no swap necessary
                if(!L1iNode->valid)
                {
                    L1iNode->tag = VCL1iNode->tag;
                    L1iNode->valid = 1;

                    // LRU policy L1i
                    if(bumpToFirst(cacheHier->L1i[currIndxL1], currTagL1) != 0)
                    {
                        fprintf(stderr,"ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                        return EXIT_FAILURE;
                    }
                    return EXIT_SUCCESS;
                }

                // move to next node in the L1i cache
                L1iNode = L1iNode->next;
            }

            // otherwise all ways have a valid tag so a swap is necesary
            ulli swapTag = cacheHier->L1i[currIndxL1]->last->tag;
            if(bumpToFirst(cacheHier->L1i[currIndxL1], swapTag) != 0)
            {
                fprintf(stderr,"ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            // swap VCL1i and L1i
            ulli tempTag = VCL1iNode->tag;
            VCL1iNode->tag = swapTag;
            cacheHier->L1i[currIndxL1]->first->tag = tempTag;

            // increment stats TODO verify this is considered a kickout
            stats->kickoutL1i++;

            return EXIT_SUCCESS;
        }

        // move to next node in the VCL1i
        VCL1iNode = VCL1iNode->next;
    }

    // entry was not in the L1i victim cache -> check L2
    if(checkL2(currTagL2, currIndxL2, cacheHier) == MISS)
    {
        stats->missL2++;

        // L2 miss
        // check the up the memory hierarchy for the requested value
        if(L2miss(currTagL2, currIndxL2, cacheHier, stats) == EXIT_FAILURE)
        {
            fprintf(stderr,"ERROR: %s: %d", __FILE__, __LINE__);
            return EXIT_FAILURE;
        }
    }
    // otherwise hit
    else
    {
        // increment stats
        stats->hitL2++;
        stats->cycleInst += L2_HIT_T;
        stats->totExecT += L2_TRANSFER_T;
    }

    // hit or miss still need to transfer value from L2 (once it is there) to L1i
    // check if there is an empty spot (not valid) in L1i
    L1iNode = cacheHier->L1i[currIndxL1]->first;
    while(L1iNode != NULL)
    {
        if(!L1iNode->valid)
        {
            // mark as valid and insert into L1i
            L1iNode->valid = 1;
            L1iNode->tag = currTagL1;

            // adhere to LRU policy
            if(bumpToFirst(cacheHier->L1i[currIndxL1], currTagL1))
            {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }

        L1iNode = L1iNode->next;
    }

    // otherwise a kickout occurs
    VCL1iNode = cacheHier->VCL1i->first;
    L1iNode = cacheHier->L1i[currIndxL1]->last;
    while(VCL1iNode != NULL)
    {
        // case 1: VCL1i has an available spot for the kickout from L1i
        if(!VCL1iNode->valid)
        {
            // transfer tag from L1i to VCL1i (L1i kickout)
            VCL1iNode->tag = L1iNode->tag;
            VCL1iNode->valid = 1;
            VCL1iNode->dirty = L1iNode->dirty;

            // LRU policy VCL1i
            if(bumpToFirst(cacheHier->VCL1i, VCL1iNode->tag))
            {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            // transfer from L2 to L1i
            L1iNode->valid = 1;
            L1iNode->tag = currTagL1;
            L1iNode->dirty = CLEAN;

            // LRU policy L1i
            if(bumpToFirst(cacheHier->L1i[currIndxL1], currTagL1))
            {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            // LRU policy L2
            if(bumpToFirst(cacheHier->L2[currIndxL2], currTagL2))
            {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            return EXIT_SUCCESS;
        }

        VCL1iNode = VCL1iNode->next;
    }

    // case 2: kickout from L1i causes a kickout from VCL1i -> move entry to L2
    VCL1iNode = cacheHier->VCL1i->last;         // item being kicked out from L1i
    L1iNode = cacheHier->L1i[currIndxL1]->last; // item being kicked out from VCL1i
    node *kickVCL1i = VCL1iNode;                // temp node
    node *L2Node = cacheHier->VCL2->first;

    // kickout from L1i to VCL1i
    VCL1iNode->tag = L1iNode->tag;
    VCL1iNode->valid = 1;
    VCL1iNode->dirty = L1iNode->dirty;
    if(bumpToFirst(cacheHier->VCL1i, VCL1iNode->tag))
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    // kickout from VCL1i to L2
    // case 2a: there is a spot available in L2
    while(L2Node != NULL)
    {
        if(!L2Node->valid)
        {
            // transfer VCL1i to L2
            L2Node->tag = kickVCL1i->tag;
            L2Node->valid = 1;
            L2Node->dirty = kickVCL1i->dirty;

            // LRU policy L2
            if(bumpToFirst(cacheHier->L2[currIndxL2], L2Node->tag))
            {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            // transfer tag from L2 to L1i
            L1iNode->tag = currTagL1;
            L1iNode->valid = 1;
            L1iNode->dirty = CLEAN;

            // LRU policy L1i
            if(bumpToFirst(cacheHier->L1i[currIndxL1], currTagL1))
            {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            return EXIT_SUCCESS;
        }
        L2Node = L2Node->next;
    }

    // case 2b:  must evict LRU item from L2
    L2Node = cacheHier->L2[currIndxL2]->last;
    node *VCL2Node = cacheHier->VCL2->first;

    // there is an spot available in VCL2 for L2 kickout
    while(VCL2Node != NULL)
    {
        if(!VCL2Node->valid)
        {
            // transfer tag L2 to VCL2
            VCL2Node->tag = L2Node->tag;
            VCL2Node->valid = 1;
            VCL2Node->dirty = L2Node->dirty;

            // LRU policy VCL2
            if(bumpToFirst(cacheHier->VCL2, VCL2Node->tag))
            {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            // transfer VCL1i to L2
            L2Node->tag = kickVCL1i->tag;
            L2Node->valid = 1;
            L2Node->dirty = kickVCL1i->dirty;

            // LRU policy L2
            if(bumpToFirst(cacheHier->L2[currIndxL2], L2Node->tag))
            {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            // transfer tag from L2 to L1i
            L1iNode->tag = currTagL1;
            L1iNode->valid = 1;
            L1iNode->dirty = CLEAN;

            // LRU policy L1i
            if(bumpToFirst(cacheHier->L1i[currIndxL1], currTagL1))
            {
                fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            return EXIT_SUCCESS;
        }

        VCL2Node = VCL2Node->next;
    }

    // case 2c: L2 is full and VCL2 is full -> kickout L2 and VCL2
    L2Node = cacheHier->L2[currIndxL2]->last;
    VCL2Node = cacheHier->VCL2->last;
    node *kickVCL2 = VCL2Node; // temp node

    // transfer L2 to VCL2
    VCL2Node->tag = L2Node->tag;
    VCL2Node->valid = 1;
    VCL2Node->dirty = L2Node->dirty;

    // LRU policy VCL2
    if(bumpToFirst(cacheHier->VCL2, VCL2Node->tag))
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    // transfer VCL1i to L2
    L2Node->tag = kickVCL1i->tag;
    L2Node->valid = 1;
    L2Node->dirty = kickVCL1i->dirty;

    // LRU policy L2
    if(bumpToFirst(cacheHier->L2[currIndxL2], L2Node->tag))
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    // transfer tag from L2 to L1i
    L1iNode->tag = currTagL1;
    L1iNode->valid = 1;
    L1iNode->dirty = CLEAN;

    // LRU policy L1i
    if(bumpToFirst(cacheHier->L1i[currIndxL1], currTagL1))
    {
        fprintf(stderr, "ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    // check if item evicted from VCL2 was dirty and needs written to main mem
    // if clean then value is discarded -> no transfer time
    if(kickVCL2->dirty == DIRTY)
    {
        // TODO add main memory write time
    }

    return EXIT_SUCCESS;
}

int L1dMiss(ulli currTagL1, ulli currTagL2, int currIndxL1, int currIndxL2, allCache *cacheHier, int dirtyBit)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
    {
        fprintf(stderr,"ERROR: cache not initialized in %s function: %s: line %d\n", __FILE__, __func__, __LINE__);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
