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
    node *VCNode = cacheHier->VCL1i[0]->first;

    /* get the node from the L1 cache */
    node *L1iNode = cacheHier->L1i[currIndxL1]->first;

    // search victim cache for the tag
    while(VCNode != NULL)
    {
        // the enty was found in the L1i victim cache
        if(VCNode->valid && VCNode->tag == currTagL1)
        {
            // move found entry to front of list (LRU policy)
            if(bumpToFirst(cacheHier->VCL1i[0], currTagL1) != 0)
            {
                fprintf(stderr,"ERROR: %s: %s: %d\n", __FILE__, __func__, __LINE__);
                return EXIT_FAILURE;
            }

            // reset VCNode to its new location
            VCNode = cacheHier->VCL1i[0]->first;

            // increment statistics for simulation
            stats->cycleInst += L1_HIT_TIME; // VC to L1 same time as an L1 hit
            stats->VChitL1i++;
            stats->transfersL1i++;

            // check if there is a way that is not valid
            while(L1iNode != NULL)
            {
                // there is a way in L1i that is not valid -> write directly to it, no swap necessary
                if(!L1iNode->valid)
                {
                    L1iNode->tag = VCNode->tag;
                    L1iNode->valid = 1;

                    // move the new L1i entry to be the LRU
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
            ulli tempTag = VCNode->tag;
            VCNode->tag = cacheHier->L1i[currIndxL1]->first->tag;
            cacheHier->L1i[currIndxL1]->first->tag = tempTag;

            // increment stats TODO verify this is considered a kickout
            stats->kickoutL1i++;

            return EXIT_SUCCESS;
        }

        // move to next node in the VCL1i
        VCNode = VCNode->next;
    }

    // entry was not in the L1i victim cache -> check L2
    if(checkL2(currTagL2, currIndxL2, cacheHier) == HIT)
    {
        // TODO increment stats

        // TODO check for a kickout when moving entry to L1

        return EXIT_SUCCESS;
    }
    // L2 miss
    else
    {
        // check the up the memory hierarchy for the requested value
        if(L2miss(currTagL2, currIndxL2, cacheHier) == EXIT_FAILURE)
        {
            fprintf(stderr,"ERROR: %s: %d", __FILE__, __LINE__);
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
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
