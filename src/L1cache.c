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
    // check for bad input
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
        PERR("cache not initialzed");

    // get the first entry in the L1 victim cache
    node *VCL1iNode = cacheHier->VCL1i->first;

    // get the first node from the L1 cache
    node *L1iNode = cacheHier->L1i[currIndxL1]->last;

    // search victim cache for the tag (VC's use full address)
    // TODO move to function check VC?
    while(VCL1iNode != NULL)
    {
        // the enty was found in the L1i victim cache
        if(VCL1iNode->valid && VCL1iNode->tag == (addr >> L1_OFFSET))
        {
            // increment statistics for simulation
            stats->cycleInst += L1_HIT_T; // VC to L1 same time as an L1 hit

#ifdef DEBUG_TIME
            printf("7:VCL1i hit: time +1\n");
#endif
            stats->VChitL1i++;

            // move found entry to front of list (LRU policy)
            if(bumpToFirst(cacheHier->VCL1i, (addr >> L1_OFFSET)) != 0)
                PERR("bumpToFirst failed");

            // reset VCL1iNode to its new location
            VCL1iNode = cacheHier->VCL1i->first;

            // swap the values in the L1i cache and VCL1i
            ulli tempTag = VCL1iNode->tag;

            VCL1iNode->tag = (L1iNode->tag << cacheCnfg->bitsIndexL1) | currIndxL1;
            VCL1iNode->valid = 1;
            VCL1iNode->dirty = CLEAN;

            L1iNode->tag = tempTag >> cacheCnfg->bitsIndexL1;
            L1iNode->valid = 1;
            L1iNode->dirty = CLEAN;

            if(bumpToFirst(cacheHier->L1i[currIndxL1], L1iNode->tag) != 0)
                PERR("bumpToFirst failed");

            return EXIT_SUCCESS;
        }

        // move to next node in the VCL1i
        VCL1iNode = VCL1iNode->next;
    }

    // entry was not in the L1i victim cache -> check L2
    if(checkL2(currTagL2, currIndxL2, cacheHier, READ) == MISS)
    {
        stats->missL2++;
        stats->cycleInst += L2_MISS_T;

#ifdef DEBUG_TIME
        printf("8:L2 miss: time +10\n");
#endif

        // L2 miss
        // check the up the memory hierarchy for the requested value
        if(L2miss(stats, cacheCnfg,  currTagL2, currIndxL2, cacheHier, addr, READ, instT) == EXIT_FAILURE)
            PERR("problem L2 miss");

        /* Account for the 'replay' time */
        stats->cycleInst += L2_HIT_T;
        #ifdef POINT_COUNT
            printf("12:L2 hit replay: \t\ttime +8\n");
        #endif
    }
    // otherwise hit
    else
    {
        // increment stats
        stats->hitL2++;
        stats->cycleInst += L2_HIT_T;

#ifdef DEBUG_TIME
        printf("9:L2 hit: time +8\n");
#endif
    }

    stats->cycleInst += L2_TRANSFER_T;
#ifdef DEBUG_TIME
    printf("10:L2->L1 transfer: time +20\n");
#endif
    stats->cycleInst += L1_HIT_T; // replay time to put value in cache
#ifdef DEBUG_TIME
    printf("10b:L2->L1 replay: time +1\n");
#endif

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
            stats->cycleInst += L1_HIT_T;

#ifdef DEBUG_TIME
            printf("11:L1->VCL1i: time +1\n");
#endif

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

            return EXIT_SUCCESS;
        }

        VCL1iNode = VCL1iNode->next;
    }

    // case 2: kickout from L1i causes a kickout from VCL1i -> move entry to L2 if dirty
    VCL1iNode = cacheHier->VCL1i->last;         // item being kicked out from VCL1i
    L1iNode = cacheHier->L1i[currIndxL1]->last; // item being kicked out from L1i

    // kickout from L1i to VCL1i
    VCL1iNode->tag = (L1iNode->tag << cacheCnfg->bitsIndexL1) | currIndxL1;
    VCL1iNode->valid = 1;
    VCL1iNode->dirty = L1iNode->dirty;
    if(bumpToFirst(cacheHier->VCL1i, VCL1iNode->tag))
        PERR("bumpToFirst failed");

    stats->kickoutL1i++;

    /* stats->cycleInst += L1_HIT_T; */
    /* printf("12:VCL1i->L2: time +1\n"); */

    // transfer tag from L2 to L1i
    L1iNode->tag = currTagL1;
    L1iNode->valid = 1;
    L1iNode->dirty = CLEAN;
    if(bumpToFirst(cacheHier->L1i[currIndxL1], L1iNode->tag))
        PERR("bumpToFirst failed");

    return EXIT_SUCCESS;
}

int L1dMiss(performance *stats, memInfo* cacheCnfg,  ulli currTagL1, ulli currTagL2, int currIndxL1, int currIndxL2, allCache *cacheHier, ulli addr, int rw, refT refType)
{
    // check for bad input
    if(cacheHier == NULL || cacheHier->L1i == NULL || cacheHier->L1d == NULL || cacheHier->L2 == NULL
        || cacheHier->VCL1i == NULL || cacheHier->VCL1d == NULL || cacheHier->VCL2 == NULL)
        PERR("cache not initialzed");

    // get the first entry in the L1 victim cache
    node *VCL1dNode = cacheHier->VCL1d->first;

    // get the last way from the L1 cache
    node *L1dNode = cacheHier->L1d[currIndxL1]->last;

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
            if(refType == dataTR)
                stats->cycleDRead += L1_HIT_T; // VC to L1 same time as an L1 hit
            else
                stats->cycleDWrite += L1_HIT_T;
#ifdef DEBUG_TIME
            printf("13:VCL1d hit: time +1\n");
#endif
            stats->VChitL1d++;

            // swap the values in the L1d cache and VCL1d
            ulli swapTag = cacheHier->L1d[currIndxL1]->last->tag;
            if(bumpToFirst(cacheHier->L1d[currIndxL1], swapTag) != 0)
                PERR("bumpToFirst failed");

            // swap the values in the L1d cache and VCL1d
            ulli tempTag = VCL1dNode->tag;
            short tempDirty = VCL1dNode->dirty;

            VCL1dNode->tag = (L1dNode->tag << cacheCnfg->bitsIndexL1) | currIndxL1;
            VCL1dNode->valid = 1;
            VCL1dNode->dirty = L1dNode->dirty;

            L1dNode->tag = tempTag >> cacheCnfg->bitsIndexL1;
            L1dNode->valid = 1;
            if(rw == READ)
                L1dNode->dirty = tempDirty;
            else
                L1dNode->dirty = DIRTY;

            if(bumpToFirst(cacheHier->L1d[currIndxL1], L1dNode->tag) != 0)
                PERR("bumpToFirst failed");

            return EXIT_SUCCESS;
        }

        // move to next node in the VCL1d
        VCL1dNode = VCL1dNode->next;
    }

    // entry was not in the L1d victim cache -> must first make write request to L2 if there is a dirty kickout
    L1dNode = cacheHier->L1d[currIndxL1]->first;
    VCL1dNode = cacheHier->VCL1d->first;
    bool L1dSpace = false;
    bool VCL1dSpace = false;
    while(L1dNode != NULL)
    {
        if(!L1dNode->valid)
        {
           L1dSpace = true;
           break;
        }
        L1dNode = L1dNode->next;
    }
    while(VCL1dNode != NULL)
    {
        if(!VCL1dNode->valid)
        {
           VCL1dSpace = true;
           break;
        }
        VCL1dNode = VCL1dNode->next;
    }

    // if no space in L1d and VCL1d then there is a kickout from L1d cache
    // if the kickout is dirty the write request to L2 must occur before checking L2 for the
    // value that originally triggered this request
    if(L1dSpace == false && VCL1dSpace == false)
    {
        if(rw == READ)
        {
            stats->cycleDRead += L1_HIT_T;
#ifdef DEBUG_TIME
            printf("14:L1dR->VCL1dR : time +1\n");
#endif
        }
        else
        {
            stats->cycleDWrite += L1_HIT_T;
#ifdef DEBUG_TIME
            printf("15:L1dW->VCL1d: time +1\n");
#endif
        }

        VCL1dNode = cacheHier->VCL1d->last;
        L1dNode = cacheHier->L1d[currIndxL1]->last;
        ulli tempTagVCL1d = VCL1dNode->tag; // tag being kickout out to L2
        short tempDirty = VCL1dNode->dirty;

        // just increment stats if kickout isn't dirty
        if(tempDirty == CLEAN)
            stats->kickoutL1d++;

        // otherwise handle dirty kickout
        else if(tempDirty == DIRTY)
        {
            if(rw == READ)
            {
                stats->cycleDRead += L2_TRANSFER_T;
                // TODO replay??
#ifdef DEBUG_TIME
                printf("16:L1dR->L2 kickout: time +20\n");
#endif

            }
            else
            {
                stats->cycleDWrite += L2_TRANSFER_T;
#ifdef DEBUG_TIME
                printf("17:L1dW->L2 kickout: time +20\n");
#endif
            }

            stats->kickoutL1d++;
            stats->dirtyKickL1d++;

            // dirty write to L2
            // convert tempTag to L2 tag format
            ulli tempaddr = tempTagVCL1d << L1_OFFSET;
            int tempIndx = (tempaddr << cacheCnfg->bitsTagL2) >> (cacheCnfg->bitsTagL2 + L2_OFFSET);
            ulli tempTag = tempaddr >> (cacheCnfg->bitsIndexL2 + L2_OFFSET);

            // check if tag is already in L2 -> if so it is marked dirty
            if(checkL2(tempTag, tempIndx, cacheHier, WRITE) == HIT)
                stats->hitL2++;

            // otherwise write value to L2
            else
            {
                stats->missL2++;

                if(L2miss(stats, cacheCnfg,  tempTag, tempIndx, cacheHier, tempaddr, WRITE, refType) == EXIT_FAILURE)
                    PERR("problem L2 miss");
                /* Account for the 'replay' time */
                stats->hitL2++;
            }
        }

        // kickout from L1d to VCL1d
        VCL1dNode->tag = (L1dNode->tag << cacheCnfg->bitsIndexL1) | currIndxL1;
        VCL1dNode->valid = 1;
        VCL1dNode->dirty = L1dNode->dirty;
        if(bumpToFirst(cacheHier->VCL1d, VCL1dNode->tag))
            PERR("bumpToFirst failed");

        // now check L2 for the original request
        if(checkL2(currTagL2, currIndxL2, cacheHier, READ) == MISS)
        {
            if(rw == READ)
            {
                stats->cycleDRead += L2_MISS_T;
#ifdef DEBUG_TIME
                printf("18:L2 miss: time +10\n");
#endif
            }
            else
            {
                stats->cycleDWrite += L2_MISS_T;
#ifdef DEBUG_TIME
                printf("19:L2 miss: time +10\n");
#endif
            }

            stats->missL2++;

            // L2 miss
            // check the up the memory hierarchy for the requested value
            if(L2miss(stats, cacheCnfg,  currTagL2, currIndxL2, cacheHier, addr, READ, refType) == EXIT_FAILURE)
                PERR("problem L2 miss");

            /* Account for the 'replay' time */
            stats->hitL2++;
        }
        // otherwise hit
        else
        {
            // increment stats
            stats->hitL2++;
            if(rw == READ)
            {
                stats->cycleDRead += L2_HIT_T;
#ifdef DEBUG_TIME
                printf("20:L2 hit: time +8\n");
#endif
            }
            else
            {
                stats->cycleDWrite += L2_HIT_T;
#ifdef DEBUG_TIME
                printf("21:L2 hit: time +8\n");
#endif
            }
        }

        // transfer tag from L2 to L1d
        if(rw == READ)
        {
            stats->cycleDRead += L2_TRANSFER_T;
            stats->cycleDRead += L1_HIT_T; // replay
#ifdef DEBUG_TIME
            printf("21:L2->L1dR: time +20\n");
            printf("21b:L2->L1dR replay: time +1\n");
#endif
        }
        else
        {
            stats->cycleDWrite += L2_TRANSFER_T;
            stats->cycleDWrite += L1_HIT_T;
#ifdef DEBUG_TIME
            printf("22:L2->L1dW: time +20\n");
            printf("22b:L2->L1dW replay: time +1\n");
#endif
        }

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

    // item was not in VCL1d and there is not a kickout from L1
    else
    {
        // entry was not in the L1d victim cache -> check L2
        if(checkL2(currTagL2, currIndxL2, cacheHier, READ) == MISS)
        {
            if(rw == READ)
            {
                stats->cycleDRead += L2_MISS_T;
#ifdef DEBUG_TIME
                printf("23:L2 miss: time +10\n");
#endif
            }
            else
            {
                stats->cycleDWrite += L2_MISS_T;
#ifdef DEBUG_TIME
                printf("24:L2 miss: time +10\n");
#endif
            }
            stats->missL2++;

            // L2 miss
            // check the up the memory hierarchy for the requested value
            if(L2miss(stats, cacheCnfg,  currTagL2, currIndxL2, cacheHier, addr, READ, refType) == EXIT_FAILURE)
                PERR("problem L2 miss");

            /* Account for the 'replay' time */
            stats->hitL2++;
        }
        // otherwise hit
        else
        {
            // increment stats
            stats->hitL2++;
            if(rw == READ)
            {
                stats->cycleDRead += L2_HIT_T;
#ifdef DEBUG_TIME
                printf("25:L2 hit: time +8\n");
#endif
            }
            else
            {
                stats->cycleDWrite += L2_HIT_T;
#ifdef DEBUG_TIME
                printf("26:L2 hit: time +8\n");
#endif
            }
        }

        // hit or miss still need to transfer value from L2 (once it is there) to L1d
        if(rw == READ)
        {
            stats->cycleDRead += L2_TRANSFER_T;
            stats->cycleDRead += L1_HIT_T;
#ifdef DEBUG_TIME
            printf("27:L2->L1dR: time +20\n");
            printf("27b:L2->L1dR replay: time +1\n");
#endif
        }
        else
        {
            stats->cycleDWrite += L2_TRANSFER_T;
            stats->cycleDWrite += L1_HIT_T;
#ifdef DEBUG_TIME
            printf("28:L2->L1dW: time +20\n");
            printf("28b:L2->L1dW replay: time +1\n");
#endif
        }

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
        // TODO these stats are not incremented
        /* if(rw == READ) */
        /* { */
        /*     stats->cycleDRead += L1_HIT_T; */
/* #ifdef DEBUG_TIME */
        /*     printf("29:L1dR->VCL1d: time +1\n"); */
/* #endif */
        /* } */
        /* else */
        /* { */
        /*     stats->cycleDWrite += L1_HIT_T; */
/* #ifdef DEBUG_TIME */
        /*     printf("30:L1dW->VCL1d: time +1\n"); */
/* #endif */
        /* } */

        while(VCL1dNode != NULL)
        {
            // VCL1d has an available spot for the kickout from L1d
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

                return EXIT_SUCCESS;
            }

            VCL1dNode = VCL1dNode->next;
        }
        PERR("all cases should be covered before this point");
    }
}
