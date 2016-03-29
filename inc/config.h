/**
 * @file        config.h
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Header file with function prototypes for configuring the cache and memory.
 */

 #ifndef CONFIG_H
     #define CONFIG_H
     #define LISTVALUES 1
     #define L1_4KB      100   /// per 4KB of L1 cache
     #define L1_ASSOC    100   /// per doubling of L1 associativity
     #define L2_16KB     50    /// per 16KB of L2 cache
     #define L2_ASSOC    50    /// per doubling of L2 associativity
     #define DECMEMLAT   200   /// to halve decrease memory latency
     #define BANDWIDTH   100   /// to double the bandwidth
     #define BASEMEMORY  75    /// TODO ?????????? NOT SURE ABOUT THIS

     #include <stdio.h>
     #include <stdlib.h>
     #include <string.h>


    /**
     * @struct memInfo
     * @brief contains variables about the memory system configuration in use
     */
    typedef struct
    {
        char cacheName[32]; ///Holds the config filename, helpful for printing
        int totalCost;   /// Total cost of the cache

        int L1dSize;    /// L1 data cache size
        int L1dWays;    /// L1 data cache ways
        int L1dBlock;   /// L1 data block size
        int L1iSize;    /// L1 instruction cache size
        int L1iWays;    /// L1 instruction cache ways
        int L1iBlock;   /// L1 instruction block size
        int L1Cost      /// L1 cost

        int L2Size;     /// L2 cache size
        int L2Ways;     /// L2 cache ways
        int L2Block;    /// L2 cache block size
        int L2Cost;     /// L2 cost

        int addrsendT;  /// main memory address send time
        int readyT;     /// main memory ready time
        int chunkT;     /// main memory chunk time
        int chunkS;     /// main memory chunk size
        int memoryCost; /// main memory cost
    } memInfo;



    /**
     * @brief reads from config file, and set the values of the cache
     * @param[out] fully populated memInfo struct
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int setCacheValues(memInfo cache);

    /**
     * @brief calculates cost of a cache
     * @param[out] fully populated memInfo struct
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
     int calculateCost(memInfo cache);


#endif //CONFIG_H
