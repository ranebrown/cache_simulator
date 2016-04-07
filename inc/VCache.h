/**
 * @file        VCache.h
 * @authors     Rane Brown & Brian Douglass
 * @date        04-06-2016
 * @brief       Function prototypes for the vicitm caches
 */

#ifndef VCACHE_H
    #define VCACHE_H

    #include <stdio.h>
    #include <stdlib.h>

    /**
     * @brief check if miss from L1i is in the victim cache
     * @param[in] addr address being checked
     * @return 0 hit, 1 miss
     */
    int checkVC_L1i(ulli addr);

    /**
     * @brief check if miss from L1d is in the victim cache
     * @param[in] addr address being checked
     * @return 0 hit, 1 miss
     */
    int checkVC_L1d(ulli addr);

    /**
     * @brief check if miss from L2 is in the victim cache
     * @param[in] addr address being checked
     * @return 0 hit, 1 miss
     */
    int checkVC_L2(ulli addr);

    /**
     * @brief inserts a block into the L1i victim cache, if an item needs removed returns it in VCkick
     * @param[out] VCkick block being removed from the victim cache (only if necessary)
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int insertVC_L1i(ulli *VCkick);

    /**
     * @brief inserts a block into the L1d victim cache, if an item needs removed returns it in VCkick
     * @param[out] VCkick block being removed from the victim cache (only if necessary)
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int insertVC_L1d(ulli *VCkick);

    /**
     * @brief inserts a block into the L2 victim cache, if an item needs removed returns it in VCkick
     * @param[out] VCkick block being removed from the victim cache (only if necessary)
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int insertVC_L2(ulli *VCkick);

#endif // VCACHE_H
