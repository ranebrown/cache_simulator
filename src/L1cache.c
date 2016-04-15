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
        PERR("cache not initialized");

    /* get the first block in the list */
    node *tmpNode = cacheHier->L1i[currIndx]->first;

    /* check each way for a hit */
    while(tmpNode != NULL)
    {
        if(tmpNode->valid && tmpNode->tag == currTag)
        {
            // move node to first way (LRU policy)
            if(bumpToFirst(cacheHier->L1i[currIndx], currTag) != 0)
                PERR("bumpToFirst failed");

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
        PERR("cache not initialized");

    /* get the first block in the list */
    node *tmpNode = cacheHier->L1d[currIndx]->first;

    /* check each way for a hit */
    while(tmpNode != NULL)
    {
        if(tmpNode->valid && tmpNode->tag == currTag)
        {
            // move node to first way (LRU policy)
            if(bumpToFirst(cacheHier->L1d[currIndx], currTag) != 0)
                PERR("bumpToFirst failed");

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
        PERR("cache not initialized");

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
               PERR("bumpToFirst failed");

            return HIT;
        }
        else
            tmpNode = tmpNode->next;
    }
    return MISS;
}

int L1iMiss(performance *stats, memInfo* cacheCnfg,  ulli currTagL1, ulli currTagL2, int currIndxL1, int currIndxL2, allCache *cacheHier, ulli addr)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
        PERR("cache not initialzed");

    /* get the first entry in the L1 victim cache */
    node *VCL1iNode = cacheHier->VCL1i->first;

    /* get the first node from the L1 cache */
    node *L1iNode = cacheHier->L1i[currIndxL1]->first;

    // search victim cache for the tag (VC's use full address)
    // TODO move to function check VC?
    while(VCL1iNode != NULL)
    {
        // the enty was found in the L1i victim cache
        if(VCL1iNode->valid && VCL1iNode->tag == (addr >> L1_OFFSET))
        {
            // move found entry to front of list (LRU policy)
            if(bumpToFirst(cacheHier->VCL1i, (addr >> L1_OFFSET)) != 0)
                PERR("bumpToFirst failed");

            // reset VCL1iNode to its new location
            VCL1iNode = cacheHier->VCL1i->first;

            // increment statistics for simulation
            stats->cycleInst += L1_HIT_T; // VC to L1 same time as an L1 hit
            stats->VChitL1i++;
            stats->transfersL1i++;

            // swap the values in the L1i cache and VCL1i
            ulli swapTag = cacheHier->L1i[currIndxL1]->last->tag;
            if(bumpToFirst(cacheHier->L1i[currIndxL1], swapTag) != 0)
                PERR("bumpToFirst failed");

            // swap VCL1i and L1i
            ulli tempTag = VCL1iNode->tag;
            // calculate VCL1i tag before swapping
            VCL1iNode->tag = (swapTag << cacheCnfg->bitsIndexL1) | currIndxL1;
            // calculate L1i tag before swapping
            cacheHier->L1i[currIndxL1]->first->tag = tempTag >> cacheCnfg->bitsIndexL1;

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
        if(L2miss(stats, cacheCnfg,  currTagL2, currIndxL2, cacheHier, addr) == EXIT_FAILURE)
            PERR("problem L2 miss");
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
                PERR("bumpToFirst failed");
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
            VCL1iNode->tag = (L1iNode->tag << cacheCnfg->bitsIndexL1) | currIndxL1;
            VCL1iNode->valid = 1;
            VCL1iNode->dirty = L1iNode->dirty;

            // LRU policy VCL1i
            if(bumpToFirst(cacheHier->VCL1i, VCL1iNode->tag))
                PERR("bumpToFirst failed");

            // transfer from L2 to L1i
            L1iNode->valid = 1;
            L1iNode->tag = currTagL1;
            L1iNode->dirty = CLEAN;

            // LRU policy L1i
            if(bumpToFirst(cacheHier->L1i[currIndxL1], currTagL1))
                PERR("bumpToFirst failed");

            // LRU policy L2
            if(bumpToFirst(cacheHier->L2[currIndxL2], currTagL2))
                PERR("bumpToFirst failed");

            return EXIT_SUCCESS;
        }

        VCL1iNode = VCL1iNode->next;
    }

    // case 2: kickout from L1i causes a kickout from VCL1i -> move entry to L2 if dirty
    VCL1iNode = cacheHier->VCL1i->last;         // item being kicked out from L1i
    L1iNode = cacheHier->L1i[currIndxL1]->last; // item being kicked out from VCL1i
    node *kickVCL1i = VCL1iNode;                // temp node
    node *L2Node = cacheHier->L2[currIndxL2]->first;

    // kickout from L1i to VCL1i
    VCL1iNode->tag = (L1iNode->tag << cacheCnfg->bitsIndexL1) | currIndxL1;
    VCL1iNode->valid = 1;
    VCL1iNode->dirty = L1iNode->dirty;
    if(bumpToFirst(cacheHier->VCL1i, VCL1iNode->tag))
        PERR("bumpToFirst failed");

    // check dirty or clean kickout
    if(kickVCL1i->dirty == CLEAN)
    {
        stats->kickoutL1i++;
        // transfer tag from L2 to L1i
        L1iNode->tag = currTagL1;
        L1iNode->valid = 1;
        L1iNode->dirty = CLEAN;
        if(bumpToFirst(cacheHier->L1i[currIndxL1], L1iNode->tag))
            PERR("bumpToFirst failed");

        return EXIT_SUCCESS;
    }
    // TODO remove below code -> never have dirty kickouts from L1i
    else
    {
        stats->dirtyKickL1i++;

        // kickout from VCL1i to L2
        // case 2a: there is a spot available in L2
        while(L2Node != NULL)
        {
            if(!L2Node->valid)
            {
                // transfer VCL1i to L2
                L2Node->tag = kickVCL1i->tag >> cacheCnfg->bitsIndexL2;
                L2Node->valid = 1;
                L2Node->dirty = kickVCL1i->dirty;

                // LRU policy L2
                if(bumpToFirst(cacheHier->L2[currIndxL2], L2Node->tag))
                    PERR("bumpToFirst failed");

                // transfer tag from L2 to L1i
                L1iNode->tag = currTagL1;
                L1iNode->valid = 1;
                L1iNode->dirty = CLEAN;

                // LRU policy L1i
                if(bumpToFirst(cacheHier->L1i[currIndxL1], currTagL1))
                    PERR("bumpToFirst failed");

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
                VCL2Node->tag = (L2Node->tag << cacheCnfg->bitsIndexL2) | currIndxL2;
                VCL2Node->valid = 1;
                VCL2Node->dirty = L2Node->dirty;

                // LRU policy VCL2
                if(bumpToFirst(cacheHier->VCL2, VCL2Node->tag))
                    PERR("bumpToFirst failed");

                // transfer VCL1i to L2
                L2Node->tag = kickVCL1i->tag >> cacheCnfg->bitsIndexL2;
                L2Node->valid = 1;
                L2Node->dirty = kickVCL1i->dirty;

                // LRU policy L2
                if(bumpToFirst(cacheHier->L2[currIndxL2], L2Node->tag))
                    PERR("bumpToFirst failed");

                // transfer tag from L2 to L1i
                L1iNode->tag = currTagL1;
                L1iNode->valid = 1;
                L1iNode->dirty = CLEAN;

                // LRU policy L1i
                if(bumpToFirst(cacheHier->L1i[currIndxL1], currTagL1))
                    PERR("bumpToFirst failed");

                return EXIT_SUCCESS;
            }

            VCL2Node = VCL2Node->next;
        }

        // case 2c: L2 is full and VCL2 is full -> kickout L2 and VCL2
        L2Node = cacheHier->L2[currIndxL2]->last;
        VCL2Node = cacheHier->VCL2->last;
        node *kickVCL2 = VCL2Node; // temp node

        // transfer L2 to VCL2
        VCL2Node->tag = (L2Node->tag << cacheCnfg->bitsIndexL2) | currIndxL2 ;
        VCL2Node->valid = 1;
        VCL2Node->dirty = L2Node->dirty;

        // LRU policy VCL2
        if(bumpToFirst(cacheHier->VCL2, VCL2Node->tag))
            PERR("bumpToFirst failed");

        // transfer VCL1i to L2
        L2Node->tag = kickVCL1i->tag >> cacheCnfg->bitsIndexL2;
        L2Node->valid = 1;
        L2Node->dirty = kickVCL1i->dirty;

        // LRU policy L2
        if(bumpToFirst(cacheHier->L2[currIndxL2], L2Node->tag))
            PERR("bumpToFirst failed");

        // transfer tag from L2 to L1i
        L1iNode->tag = currTagL1;
        L1iNode->valid = 1;
        L1iNode->dirty = CLEAN;

        // LRU policy L1i
        if(bumpToFirst(cacheHier->L1i[currIndxL1], currTagL1))
            PERR("bumpToFirst failed");

        // check if item evicted from VCL2 was dirty and needs written to main mem
        if(kickVCL2->dirty == CLEAN)
            stats->kickoutL2++;
        else
        {
            stats->dirtyKickL2++;
            // TODO add main memory transfer stats
        }

        return EXIT_SUCCESS;
    }
}

int L1dMiss(performance *stats, memInfo* cacheCnfg,  ulli currTagL1, ulli currTagL2, int currIndxL1, int currIndxL2, allCache *cacheHier, ulli addr, int rw)
{
    /* check for bad input */
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
        PERR("cache not initialzed");

    /* get the first entry in the L1 victim cache */
    node *VCL1dNode = cacheHier->VCL1d->first;

    /* get the first node from the L1 cache */
    node *L1dNode = cacheHier->L1d[currIndxL1]->first;

    // search victim cache for the tag (VC's use full address)
    while(VCL1dNode != NULL)
    {
        // the enty was found in the L1d victim cache
        if(VCL1dNode->valid && VCL1dNode->tag == (addr >> L1_OFFSET))
        {
            // move found entry to front of list (LRU policy)
            if(bumpToFirst(cacheHier->VCL1d, (addr >> L1_OFFSET)) != 0)
                PERR("bumpToFirst failed");

            // reset VCL1dNode to its new location
            VCL1dNode = cacheHier->VCL1d->first;

            // increment statistics for simulation
            stats->cycleInst += L1_HIT_T; // VC to L1 same time as an L1 hit
            stats->VChitL1d++;
            stats->transfersL1d++;

            // swap the values in the L1d cache and VCL1d
            ulli swapTag = cacheHier->L1d[currIndxL1]->last->tag;
            if(bumpToFirst(cacheHier->L1d[currIndxL1], swapTag) != 0)
                PERR("bumpToFirst failed");

            // swap VCL1d and L1d
            ulli tempTag = VCL1dNode->tag;
            // calculate VCL1d tag before swapping
            VCL1dNode->tag = (swapTag << cacheCnfg->bitsIndexL1) | currIndxL1;
            // calculate L1d tag before swapping
            cacheHier->L1d[currIndxL1]->first->tag = tempTag >> cacheCnfg->bitsIndexL1;

            // set dirty bit
            if(rw == READ)
                cacheHier->L1d[currIndxL1]->first->dirty = CLEAN;
            else
                cacheHier->L1d[currIndxL1]->first->dirty = DIRTY;

            return EXIT_SUCCESS;
        }

        // move to next node in the VCL1d
        VCL1dNode = VCL1dNode->next;
    }

    // entry was not in the L1d victim cache -> check L2
    if(checkL2(currTagL2, currIndxL2, cacheHier) == MISS)
    {
        stats->missL2++;

        // L2 miss
        // check the up the memory hierarchy for the requested value
        if(L2miss(stats, cacheCnfg,  currTagL2, currIndxL2, cacheHier, addr) == EXIT_FAILURE)
            PERR("problem L2 miss");
    }
    // otherwise hit
    else
    {
        // increment stats
        stats->hitL2++;
        stats->cycleInst += L2_HIT_T;
        stats->totExecT += L2_TRANSFER_T;
    }

    // hit or miss still need to transfer value from L2 (once it is there) to L1d
    // check if there is an empty spot (not valid) in L1d
    L1dNode = cacheHier->L1d[currIndxL1]->first;
    while(L1dNode != NULL)
    {
        if(!L1dNode->valid)
        {
            // mark as valid and insert into L1d
            L1dNode->valid = 1;
            L1dNode->tag = currTagL1;
            if(rw == READ)
                L1dNode->dirty = CLEAN;
            else
                L1dNode->dirty = DIRTY;

            // adhere to LRU policy
            if(bumpToFirst(cacheHier->L1d[currIndxL1], currTagL1))
                PERR("bumpToFirst failed");
            return EXIT_SUCCESS;
        }

        L1dNode = L1dNode->next;
    }

    // otherwise a kickout occurs
    VCL1dNode = cacheHier->VCL1d->first;
    L1dNode = cacheHier->L1d[currIndxL1]->last;
    while(VCL1dNode != NULL)
    {
        // case 1: VCL1d has an available spot for the kickout from L1d
        if(!VCL1dNode->valid)
        {
            // transfer tag from L1d to VCL1d (L1d kickout)
            VCL1dNode->tag = (L1dNode->tag << cacheCnfg->bitsIndexL1) | currIndxL1;
            VCL1dNode->valid = 1;
            VCL1dNode->dirty = L1dNode->dirty;

            // LRU policy VCL1d
            if(bumpToFirst(cacheHier->VCL1d, VCL1dNode->tag))
                PERR("bumpToFirst failed");

            // transfer from L2 to L1d
            L1dNode->valid = 1;
            L1dNode->tag = currTagL1;
            if(rw == READ)
                L1dNode->dirty = CLEAN;
            else
                L1dNode->dirty = DIRTY;

            // LRU policy L1d
            if(bumpToFirst(cacheHier->L1d[currIndxL1], currTagL1))
                PERR("bumpToFirst failed");

            // LRU policy L2
            if(bumpToFirst(cacheHier->L2[currIndxL2], currTagL2))
                PERR("bumpToFirst failed");

            return EXIT_SUCCESS;
        }

        VCL1dNode = VCL1dNode->next;
    }

    // case 2: kickout from L1d causes a kickout from VCL1d -> move entry to L2 if dirty
    VCL1dNode = cacheHier->VCL1d->last;
    L1dNode = cacheHier->L1d[currIndxL1]->last;
    node *kickVCL1d = VCL1dNode;                // temp node
    node *L2Node = cacheHier->L2[currIndxL2]->first;

    // kickout from L1d to VCL1d
    VCL1dNode->tag = (L1dNode->tag << cacheCnfg->bitsIndexL1) | currIndxL1;
    VCL1dNode->valid = 1;
    VCL1dNode->dirty = L1dNode->dirty;
    if(bumpToFirst(cacheHier->VCL1d, VCL1dNode->tag))
        PERR("bumpToFirst failed");

    // check dirty or clean kickout
    if(kickVCL1d->dirty == CLEAN)
    {
        stats->kickoutL1d++;
        // transfer tag from L2 to L1d
        L1dNode->tag = currTagL1;
        L1dNode->valid = 1;
        if(rw == READ)
            L1dNode->dirty = CLEAN;
        else
            L1dNode->dirty = DIRTY;
        if(bumpToFirst(cacheHier->L1d[currIndxL1], L1dNode->tag))
            PERR("bumpToFirst failed");

        return EXIT_SUCCESS;
    }
    else
    {
        stats->dirtyKickL1d++;
        // transfer tag from L2 to L1d
        L1dNode->tag = currTagL1;
        L1dNode->valid = 1;
        if(rw == READ)
            L1dNode->dirty = CLEAN;
        else
            L1dNode->dirty = DIRTY;
        if(bumpToFirst(cacheHier->L1d[currIndxL1], L1dNode->tag))
            PERR("bumpToFirst failed");

        // kickout from VCL1d to L2
        // case 2a: there is a spot available in L2
        while(L2Node != NULL)
        {
            if(!L2Node->valid)
            {
                // transfer VCL1d to L2
                L2Node->tag = kickVCL1d->tag >> cacheCnfg->bitsIndexL2;
                L2Node->valid = 1;
                L2Node->dirty = kickVCL1d->dirty;

                // LRU policy L2
                if(bumpToFirst(cacheHier->L2[currIndxL2], L2Node->tag))
                    PERR("bumpToFirst failed");

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
                VCL2Node->tag = (L2Node->tag << cacheCnfg->bitsIndexL2) | currIndxL2;
                VCL2Node->valid = 1;
                VCL2Node->dirty = L2Node->dirty;

                // LRU policy VCL2
                if(bumpToFirst(cacheHier->VCL2, VCL2Node->tag))
                    PERR("bumpToFirst failed");

                // transfer VCL1d to L2
                L2Node->tag = kickVCL1d->tag >> cacheCnfg->bitsIndexL2;
                L2Node->valid = 1;
                L2Node->dirty = kickVCL1d->dirty;

                // LRU policy L2
                if(bumpToFirst(cacheHier->L2[currIndxL2], L2Node->tag))
                    PERR("bumpToFirst failed");

                return EXIT_SUCCESS;
            }

            VCL2Node = VCL2Node->next;
        }

        // case 2c: L2 is full and VCL2 is full -> kickout L2 and VCL2
        L2Node = cacheHier->L2[currIndxL2]->last;
        VCL2Node = cacheHier->VCL2->last;
        node *kickVCL2 = VCL2Node; // temp node

        // transfer L2 to VCL2
        VCL2Node->tag = (L2Node->tag << cacheCnfg->bitsIndexL2) | currIndxL2 ;
        VCL2Node->valid = 1;
        VCL2Node->dirty = L2Node->dirty;

        // LRU policy VCL2
        if(bumpToFirst(cacheHier->VCL2, VCL2Node->tag))
            PERR("bumpToFirst failed");

        // transfer VCL1d to L2
        L2Node->tag = kickVCL1d->tag >> cacheCnfg->bitsIndexL2;
        L2Node->valid = 1;
        L2Node->dirty = kickVCL1d->dirty;

        // LRU policy L2
        if(bumpToFirst(cacheHier->L2[currIndxL2], L2Node->tag))
            PERR("bumpToFirst failed");

        // check if item evicted from VCL2 was dirty and needs written to main mem
        if(kickVCL2->dirty == CLEAN)
            stats->kickoutL2++;
        else
        {
            stats->dirtyKickL2++;
            // TODO add main memory transfer stats
        }

        return EXIT_SUCCESS;
    }
}
