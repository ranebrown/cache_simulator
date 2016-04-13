/**
 * @file        L2cache.c
 * @authors     Rane Brown & Brian Douglass
 * @date        04-06-2016
 * @brief       Functions for the L2 cache
 */

#include "L2cache.h"

int checkL2(ulli currTag, ulli currIndx, allCache *cacheHier)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
        PERR("cache not initialized");

    /* get the first block in the list */
    node *tmpNode = cacheHier->L2[currIndx]->first;

    /* check each way for a hit */
    while(tmpNode != NULL)
    {
        if(tmpNode->valid && tmpNode->tag == currTag)
        {
            // move node to first way (LRU policy)
            if(bumpToFirst(cacheHier->L2[currIndx], currTag) != 0)
                PERR("bumpToFirst failed");

            return HIT;
        }
        else
            tmpNode = tmpNode->next;
    }
    return MISS;
}

int L2miss(performance *stats, ulli currTagL2, ulli currIndxL2, allCache *cacheHier)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
        PERR("cache not initialized");

    // check the victim cache
    node *VCL2Node = cacheHier->VCL2->first;
    node *L2Node = cacheHier->L2[currIndxL2]->first;

    // search victim cache for the tag
    while(VCL2Node != NULL)
    {
        // the enty was found in the L2 victim cache
        if(VCL2Node->valid && VCL2Node->tag == currTagL2)
        {
            // move found entry to front of list (LRU policy)
            if(bumpToFirst(cacheHier->VCL2, currTagL2) != 0)
                PERR("bumpToFirst failed");

            // reset VCL2Node to its new location
            VCL2Node = cacheHier->VCL2->first;

            // increment statistics for simulation
            stats->cycleInst += L1_HIT_T; // VC to L1 same time as an L1 hit
            stats->VChitL2++;
            stats->transfersL2++;

            // check if there is a way that is not valid
            while(L2Node != NULL)
            {
                // there is a way in L2 that is not valid -> write directly to it, no swap necessary
                if(!L2Node->valid)
                {
                    L2Node->tag = VCL2Node->tag;
                    L2Node->valid = 1;

                    // move the new L2 entry to be the LRU
                    if(bumpToFirst(cacheHier->L2[currIndxL2], currTagL2) != 0)
                        PERR("bumpToFirst failed");
                    return EXIT_SUCCESS;
                }

                // move to next node in the L2 cache
                L2Node = L2Node->next;
            }

            // otherwise all ways have a valid tag so a swap is necesary
            ulli swapTag = cacheHier->L2[currIndxL2]->last->tag;
            if(bumpToFirst(cacheHier->L2[currIndxL2], swapTag) != 0)
                PERR("bumpToFirst failed");

            // swap VCL2 and L2
            ulli tempTag = VCL2Node->tag;
            VCL2Node->tag = swapTag;
            cacheHier->L2[currIndxL2]->first->tag = tempTag;

            // increment stats TODO verify this is considered a kickout
            stats->kickoutL2++;

            return EXIT_SUCCESS;
        }

        // move to next node in the VCL2
        VCL2Node = VCL2Node->next;
    }

    // if not in VCL2 need to transfer from main memory
    L2Node = cacheHier->L2[currIndxL2]->first;
    // check if there is a way that is not valid
    while(L2Node != NULL)
    {
        // there is a way in L2 that is not valid -> write directly to it
        if(!L2Node->valid)
        {
            L2Node->tag = currTagL2;
            L2Node->valid = 1;

            // move the new L2 entry to be the LRU
            if(bumpToFirst(cacheHier->L2[currIndxL2], currTagL2) != 0)
                PERR("bumpToFirst failed");
            return EXIT_SUCCESS;
        }

        // move to next node in the L2 cache
        L2Node = L2Node->next;
    }

    // need to evict an item from L2 to VCL2
    L2Node = cacheHier->L2[currIndxL2]->last; // node being evicted
    VCL2Node = cacheHier->VCL2->first;
    while(VCL2Node != NULL)
    {
        if(!VCL2Node->valid)
        {
            // transfer item being evicted from L2 to VCL2
            VCL2Node->tag = L2Node->tag;
            VCL2Node->valid = 1;
            VCL2Node->dirty = L2Node->dirty;

            // LRU policy VCL2
            if(bumpToFirst(cacheHier->VCL2, VCL2Node->tag) != 0)
                PERR("bumpToFirst failed");

            // transfer item from main memory to L2
            L2Node->tag = currTagL2;
            L2Node->valid = 1;
            L2Node->dirty = CLEAN;

            // LRU policy L2
            if(bumpToFirst(cacheHier->L2[currIndxL2], currTagL2) != 0)
                PERR("bumpToFirst failed");

            return EXIT_SUCCESS;
        }

        VCL2Node = VCL2Node->next;
    }

    // evict item from L2 and VCL2
    L2Node = cacheHier->L2[currIndxL2]->last;
    VCL2Node = cacheHier->VCL2->last;

    // check for dirty kickout from VCL2
    if(VCL2Node->dirty == DIRTY)
    {
        // TODO increment stats
    }
    VCL2Node->tag = L2Node->tag;
    VCL2Node->valid = 1;
    VCL2Node->dirty = L2Node->dirty;

    // LRU policy VCL2
    if(bumpToFirst(cacheHier->VCL2, VCL2Node->tag) != 0)
        PERR("bumpToFirst failed");

    // transfer item from main memory to L2
    L2Node->tag = currTagL2;
    L2Node->valid = 1;
    L2Node->dirty = CLEAN;

    // LRU policy L2
    if(bumpToFirst(cacheHier->L2[currIndxL2], currTagL2) != 0)
        PERR("bumpToFirst failed");

    return EXIT_SUCCESS;
}
