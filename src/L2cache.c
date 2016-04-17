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

int L2miss(performance *stats, memInfo *cacheCnfg, ulli currTagL2, ulli currIndxL2, allCache *cacheHier, ulli addr)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
        PERR("cache not initialzed");

    /* get the first entry in the L2 victim cache */
    node *VCL2Node = cacheHier->VCL2->first;

    /* get the first node from the L2 cache */
    node *L2Node = cacheHier->L2[currIndxL2]->first;

    // search victim cache for the tag (VC's use full address)
    while(VCL2Node != NULL)
    {
        // the enty was found in the L2 victim cache
        if(VCL2Node->valid && VCL2Node->tag == (addr >> L2_OFFSET))
        {
            // move found entry to front of list (LRU policy)
            if(bumpToFirst(cacheHier->VCL2, (addr >> L2_OFFSET)) != 0)
                PERR("bumpToFirst failed");

            // reset VCL2Node to its new location
            VCL2Node = cacheHier->VCL2->first;

            // increment statistics for simulation
            stats->cycleInst += L2_HIT_T;
            stats->VChitL2++;
            stats->transfersL2++;

            // swap the values in the L2 cache and VCL2
            ulli swapTag = cacheHier->L2[currIndxL2]->last->tag;
            if(bumpToFirst(cacheHier->L2[currIndxL2], swapTag) != 0)
                PERR("bumpToFirst failed");

            // swap VCL2 and L2
            ulli tempTag = VCL2Node->tag;
            // calculate VCL2 tag before swapping
            VCL2Node->tag = (swapTag << cacheCnfg->bitsIndexL2) | currIndxL2;
            // calculate L2 tag before swapping
            cacheHier->L2[currIndxL2]->first->tag = tempTag >> cacheCnfg->bitsIndexL2;

            return EXIT_SUCCESS;
        }

        // move to next node in the VCL2
        VCL2Node = VCL2Node->next;
    }

    // transfer value from main memory to L2
    // check if there is an empty spot (not valid) in L2
    L2Node = cacheHier->L2[currIndxL2]->first;
    while(L2Node != NULL)
    {
        if(!L2Node->valid)
        {
            // mark as valid and insert into L2
            L2Node->valid = 1;
            L2Node->tag = currTagL2;
            L2Node->dirty = CLEAN;

            // adhere to LRU policy
            if(bumpToFirst(cacheHier->L2[currIndxL2], currTagL2))
                PERR("bumpToFirst failed");
            return EXIT_SUCCESS;
        }

        L2Node = L2Node->next;
    }

    // otherwise a kickout occurs
    VCL2Node = cacheHier->VCL2->first;
    L2Node = cacheHier->L2[currIndxL2]->last;
    while(VCL2Node != NULL)
    {
        // case 1: VCL2 has an available spot for the kickout from L2
        if(!VCL2Node->valid)
        {
            // transfer tag from L2 to VCL2
            VCL2Node->tag = (L2Node->tag << cacheCnfg->bitsIndexL2) | currIndxL2;
            VCL2Node->valid = 1;
            VCL2Node->dirty = L2Node->dirty;

            // LRU policy VCL2
            if(bumpToFirst(cacheHier->VCL2, VCL2Node->tag))
                PERR("bumpToFirst failed");

            // transfer from main mem to L2
            L2Node->valid = 1;
            L2Node->tag = currTagL2;
            L2Node->dirty = CLEAN;

            // LRU policy L2
            if(bumpToFirst(cacheHier->L2[currIndxL2], currTagL2))
                PERR("bumpToFirst failed");

            return EXIT_SUCCESS;
        }

        VCL2Node = VCL2Node->next;
    }

    // case 2: kickout from L2 causes a kickout from VCL2 -> move entry to main mem if dirty
    VCL2Node = cacheHier->VCL2->last;
    L2Node = cacheHier->L2[currIndxL2]->last;
    node *kickVCL2 = VCL2Node;

    // kickout from L2 to VCL2
    VCL2Node->tag = (L2Node->tag << cacheCnfg->bitsIndexL2) | currIndxL2;
    VCL2Node->valid = 1;
    VCL2Node->dirty = L2Node->dirty;
    if(bumpToFirst(cacheHier->VCL2, VCL2Node->tag))
        PERR("bumpToFirst failed");

    // check dirty or clean kickout
    if(kickVCL2->dirty == CLEAN)
    {
        stats->kickoutL2++;
        // transfer tag from main memory to L2
        L2Node->tag = currTagL2;
        L2Node->valid = 1;
        L2Node->dirty = CLEAN;
        printCurrCache(cacheCnfg, cacheHier);
        
        return EXIT_SUCCESS;
    }
    else
    {
        stats->dirtyKickL2++;

        return EXIT_SUCCESS;
    }
}
