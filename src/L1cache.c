/**
 * @file        L1cache.c
 * @authors     Rane Brown & Brian Douglass
 * @date        04-06-2016
 * @brief       Function for the L1 cache
 */

#include "L1cache.h"

int checkL1i(ulli addr)
{
    return HIT;
}

int checkL1d(ulli addr)
{
    return HIT;
}

int insertL1i(ulli addr)
{
    return EXIT_SUCCESS;
}

int insertL1d(ulli addr)
{
    return EXIT_SUCCESS;
}
