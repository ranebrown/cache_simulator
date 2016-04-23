/**
 * @file        config.h
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Header file with function prototypes for configuring the cache and memory.
 */

 #ifndef CONFIG_H
    #define CONFIG_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    #include "common.h"

    //#define PRINTVALUES         ///< print statements for debugging
    #define L1_4KB        100   ///< cost value
    #define L1_ASSOC      100   ///< cost value
    #define L2_16KB       50    ///< cost value
    #define L2_ASSOC      50    ///< cost value
    #define DECMEMLAT     200   ///< to halve decrease memory latency
    #define BANDWIDTH     100   ///< to double the bandwidth
    // #define L1_HIT_TIME   1     ///<  L1 hit time
    // #define L1_MISS_TIME  1     ///<  L1 miss time
    // #define L2_HIT_TIME   8     ///<  L2 hit time
    // #define L2_MISS_TIME  10    ///<  L2 miss time
    // #define L2_TRANS_TIME 10    ///< transfer L1 to/from L2
    // #define L2_BUS_WIDTH  16    ///<  L1 to L2 bus width


    /**
     * @struct memInfo
     * @brief contains variables about the memory system configuration in use
     */
    typedef struct
    {
        int totalCost;       ///< Total cost of the cache
        int L1TotCost;       ///< L1 cost of data + instruction

        int L1dSize;         ///< L1 data cache size
        int L1dWays;         ///< L1 data cache ways
        int L1dBlock;        ///< L1 data block size
        int L1dCost;         ///< L1 data cost

        int L1iSize;         ///< L1 instruction cache size
        int L1iWays;         ///< L1 instruction cache ways
        int L1iBlock;        ///< L1 instruction block size
        int L1iCost;         ///< L1 instruction cost

        int L2Size;          ///< L2 cache size
        int L2Ways;          ///< L2 cache ways
        int L2Block;         ///< L2 cache block size
        int L2Cost;          ///< L2 cost

        int addrsendT;       ///< main memory address send time
        int readyT;          ///< main memory ready time
        int chunkT;          ///< main memory chunk time
        int chunkS;          ///< main memory chunk size
        int memoryCost;      ///< main memory cost

        int bitsIndexL1;     ///< number of bits for L1 index
        int bitsTagL1;       ///< number of bits for L1 tag
        int bitsIndexL2;     ///< number of bits for L2 index
        int bitsTagL2;       ///< number of bits for L2 tag

        char cacheName[128];  ///< the config filename, helpful for printing
    } memInfo;



    /**
     * @brief reads from config file, and set the values of the cache
     * @param[out] cache pointer to fully populated memInfo struct
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int setCacheValues(memInfo *cacheCnfg);

    /**
     * @brief calculates cost of a cache
     * @param[out] cache pointer to fully populated memInfo struct
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int calculateCost(memInfo *cache);

    /**
     * @brief pulls a name out of a file path
     *  This requires that the name is in the standard project file path.
     * @param[out] name of the file passed in
     */
    char *getName(char *str);

#endif //CONFIG_H
