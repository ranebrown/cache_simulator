/**
 * @file        config.h
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Header file with function prototypes for configuring the cache and memory.
 */

 #ifndef CONFIG_H
     #define CONFIG_H
     #define LISTVALUES 1

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
        int L1dSize;    /// L1 data cache size
        int L1dWays;    /// L1 data cache ways
        int L1dBlock;   /// L1 data block size
        int L1iSize;    /// L1 instruction cache size
        int L1iWays;    /// L1 instruction cache ways
        int L1iBlock;   /// L1 instruction block size
        int L2Size;     /// L2 cache size
        int L2Ways;     /// L2 cache ways
        int L2Block;    /// L2 cache block size
        int addrsendT;  /// main memory address send time
        int readyT;     /// main memory ready time
        int chunkT;     /// main memory chunk time
        int chunkS;     /// main memory chunk size
    } memInfo;



    /**
     * @brief reads from config file, and set the values of the cache
     * @param[out] fully populated memInfo struct
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int setCacheValues(memInfo cache);

#endif //CONFIG_H
