/**
 * @file        VCache.c
 * @authors     Rane Brown & Brian Douglass
 * @date        04-06-2016
 * @brief       Functions for the vicitm caches
 */

#include "VCache.h"

int checkVC_L1i(ulli addr)
{
    return HIT;
}

int checkVC_L1d(ulli addr)
{
    return HIT;
}

int checkVC_L2(ulli addr)
{
    return HIT;
}

int insertVC_L1i(ulli *VCkick)
{
    return EXIT_SUCCESS;
}

int insertVC_L1d(ulli *VCkick)
{
    return EXIT_SUCCESS;
}

int insertVC_L2(ulli *VCkick)
{
    return EXIT_SUCCESS;
}
