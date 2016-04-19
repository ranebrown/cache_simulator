/**
 * @file        L2cache.c
 * @authors     Rane Brown & Brian Douglass
 * @date        04-06-2016
 * @brief       Functions for the L2 cache
 */

#include "L2cache.h"

<<<<<<< HEAD
int checkL2(ulli currTag, ulli currIndx, allCache *cacheHier, int rw)
=======
int checkL2(ulli currTag, ulli currIndx, allCache *cacheHier)
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77
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
<<<<<<< HEAD
            if(rw == WRITE)
                tmpNode->dirty = DIRTY;

=======
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77
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

<<<<<<< HEAD
int L2miss(performance *stats, memInfo *cacheCnfg, ulli currTagL2, ulli currIndxL2, allCache *cacheHier, ulli addr, int rw)
{
    // check for bad input
=======
int L2miss(performance *stats, memInfo *cacheCnfg, ulli currTagL2, ulli currIndxL2, allCache *cacheHier, ulli addr)
{
    /* check for bad input */
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
        PERR("cache not initialzed");

<<<<<<< HEAD
    // get the first entry in the L2 victim cache
    node *VCL2Node = cacheHier->VCL2->first;

    // get the last way from the L2 cache
    node *L2Node = cacheHier->L2[currIndxL2]->last;
=======
    /* get the first entry in the L2 victim cache */
    node *VCL2Node = cacheHier->VCL2->first;

    /* get the first node from the L2 cache */
    node *L2Node = cacheHier->L2[currIndxL2]->first;
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77

    // search victim cache for the tag (VC's use full address)
    while(VCL2Node != NULL)
    {
<<<<<<< HEAD
        // the entry was found in the L2 victim cache
=======
        // the enty was found in the L2 victim cache
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77
        if(VCL2Node->valid && VCL2Node->tag == (addr >> L2_OFFSET))
        {
            // move found entry to front of list (LRU policy)
            if(bumpToFirst(cacheHier->VCL2, (addr >> L2_OFFSET)) != 0)
                PERR("bumpToFirst failed");

            // reset VCL2Node to its new location
            VCL2Node = cacheHier->VCL2->first;

            // increment statistics for simulation
<<<<<<< HEAD
            stats->totExecT += L2_HIT_T;
=======
            stats->cycleInst += L2_HIT_T;
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77
            stats->VChitL2++;
            stats->transfersL2++;

            // swap the values in the L2 cache and VCL2
            ulli swapTag = cacheHier->L2[currIndxL2]->last->tag;
            if(bumpToFirst(cacheHier->L2[currIndxL2], swapTag) != 0)
                PERR("bumpToFirst failed");

<<<<<<< HEAD
            // swap the values in the L2 cache and VCL2
            ulli tempTag = VCL2Node->tag;
            short tempDirty = VCL2Node->dirty;

            VCL2Node->tag = (L2Node->tag << cacheCnfg->bitsIndexL2) | currIndxL2;
            VCL2Node->valid = 1;
            VCL2Node->dirty = L2Node->dirty;

            L2Node->tag = tempTag >> cacheCnfg->bitsIndexL2;
            L2Node->valid = 1;
            if(rw == READ)
                L2Node->dirty = tempDirty;
            else
                L2Node->dirty = DIRTY;

            if(bumpToFirst(cacheHier->L2[currIndxL2], L2Node->tag) != 0)
                PERR("bumpToFirst failed");
=======
            // swap VCL2 and L2
            ulli tempTag = VCL2Node->tag;
            // calculate VCL2 tag before swapping
            VCL2Node->tag = (swapTag << cacheCnfg->bitsIndexL2) | currIndxL2;
            // calculate L2 tag before swapping
            cacheHier->L2[currIndxL2]->first->tag = tempTag >> cacheCnfg->bitsIndexL2;
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77

            return EXIT_SUCCESS;
        }

        // move to next node in the VCL2
        VCL2Node = VCL2Node->next;
    }

<<<<<<< HEAD
    // hit or miss still need to transfer value from main mem to L2
=======
    // transfer value from main memory to L2
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77
    // check if there is an empty spot (not valid) in L2
    L2Node = cacheHier->L2[currIndxL2]->first;
    while(L2Node != NULL)
    {
        if(!L2Node->valid)
        {
            // mark as valid and insert into L2
            L2Node->valid = 1;
            L2Node->tag = currTagL2;
<<<<<<< HEAD
            if(rw == READ)
                L2Node->dirty = CLEAN;
            else
                L2Node->dirty = DIRTY;
=======
            L2Node->dirty = CLEAN;
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77

            // adhere to LRU policy
            if(bumpToFirst(cacheHier->L2[currIndxL2], currTagL2))
                PERR("bumpToFirst failed");
<<<<<<< HEAD

            //increment the statistics
            stats->totExecT += MAIN_MEM_TRANSFER_T;

=======
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77
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
<<<<<<< HEAD
            // transfer tag from L2 to VCL2 (L2 kickout)
=======
            // transfer tag from L2 to VCL2
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77
            VCL2Node->tag = (L2Node->tag << cacheCnfg->bitsIndexL2) | currIndxL2;
            VCL2Node->valid = 1;
            VCL2Node->dirty = L2Node->dirty;

            // LRU policy VCL2
            if(bumpToFirst(cacheHier->VCL2, VCL2Node->tag))
                PERR("bumpToFirst failed");

            // transfer from main mem to L2
            L2Node->valid = 1;
            L2Node->tag = currTagL2;
<<<<<<< HEAD
            if(rw == READ)
                L2Node->dirty = CLEAN;
            else
                L2Node->dirty = DIRTY;
=======
            L2Node->dirty = CLEAN;
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77

            // LRU policy L2
            if(bumpToFirst(cacheHier->L2[currIndxL2], currTagL2))
                PERR("bumpToFirst failed");

<<<<<<< HEAD
            //increment the statistics
            stats->totExecT += MAIN_MEM_TRANSFER_T;

=======
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77
            return EXIT_SUCCESS;
        }

        VCL2Node = VCL2Node->next;
    }

    // case 2: kickout from L2 causes a kickout from VCL2 -> move entry to main mem if dirty
    VCL2Node = cacheHier->VCL2->last;
    L2Node = cacheHier->L2[currIndxL2]->last;
<<<<<<< HEAD
    short tempDirty = VCL2Node->dirty;
=======
    node *kickVCL2 = VCL2Node;
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77

    // kickout from L2 to VCL2
    VCL2Node->tag = (L2Node->tag << cacheCnfg->bitsIndexL2) | currIndxL2;
    VCL2Node->valid = 1;
    VCL2Node->dirty = L2Node->dirty;
    if(bumpToFirst(cacheHier->VCL2, VCL2Node->tag))
        PERR("bumpToFirst failed");

    // check dirty or clean kickout
<<<<<<< HEAD
    if(tempDirty == CLEAN)
    {
        //increment the statistics
        stats->totExecT += MAIN_MEM_TRANSFER_T;
        stats->kickoutL2++;

        // transfer tag from main mem to L2
        L2Node->tag = currTagL2;
        L2Node->valid = 1;
        if(rw == READ)
            L2Node->dirty = CLEAN;
        else
            L2Node->dirty = DIRTY;
        if(bumpToFirst(cacheHier->L2[currIndxL2], L2Node->tag))
            PERR("bumpToFirst failed");

=======
    if(kickVCL2->dirty == CLEAN)
    {
        stats->kickoutL2++;
        // transfer tag from main memory to L2
        L2Node->tag = currTagL2;
        L2Node->valid = 1;
        L2Node->dirty = CLEAN;
        printCurrCache(cacheCnfg, cacheHier);
        
>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77
        return EXIT_SUCCESS;
    }
    else
    {
<<<<<<< HEAD
        //increment the statistics
        stats->totExecT += MAIN_MEM_TRANSFER_T;
        stats->kickoutL2++;
        stats->dirtyKickL2++;

        // transfer tag from main mem to L2
        L2Node->tag = currTagL2;
        L2Node->valid = 1;
        if(rw == READ)
            L2Node->dirty = CLEAN;
        else
            L2Node->dirty = DIRTY;
        if(bumpToFirst(cacheHier->L2[currIndxL2], L2Node->tag))
            PERR("bumpToFirst failed");

        // dirty write to main mem
        // TODO increment stats for write to main mem.......DONE
=======
        stats->dirtyKickL2++;

>>>>>>> b1431a5ce78a09bccdc5747b4a260f828553af77
        return EXIT_SUCCESS;
    }
}
