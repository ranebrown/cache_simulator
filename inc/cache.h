/**
 * @file        cache.h
 * @authors     Rane Brown & Brian Douglass
 * @date        04-01-2016
 * @brief       Function prototypes shared between all cache levels
 */
#ifndef CACHE_H
    #define CACHE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "config.h"
    #include "dlinkedList.h"
    #include "common.h"


    #define HIT 0                   ///< used as a return value for a cache hit
    #define MISS 1                  ///< used as a return value for a cache miss
    #define L1_OFFSET 5             ///< L1 is 32 bytes i.e. 2^5
    #define L2_OFFSET 6             ///< L2 is 64 bytes i.e. 2^6
    #define CLEAN 0                 ///< dirty bit status
    #define DIRTY 1                 ///< dirty bit status
    #define READ 0  ///< data read operation
    #define WRITE 1 ///< data write operation

    /*
     * Defines used for tracking simulation times
     * The hit time is the time to return an item that is a hit in a cache.
     * The miss time is the time to determine that an item has missed and the time to make the request to the next cache level.
     */
    #define L1_HIT_T 1              ///< number of cycles to return an L1 hit
    #define L1_MISS_T 1             ///< number of cycles to determine an L1 request is a miss and make request to L2
    #define L2_HIT_T 8              ///< number of cycles to return an L2 hit
    #define L2_MISS_T 10            ///< number of cycles to determine an L2 request is a miss and make request to main memory
    #define L2_TRANSFER_T 20        ///< time to transfer a value from L2 to L1 cache (based on 16 byte bus)
    #define MAIN_MEM_TRANSFER_T 180 ///< time to transfer a value from main memory to L2 cache

    /**
     * @brief determines if request is data or instruction - value is passed to L2 to determine cycles
     */
    typedef enum
    {
        dataTR,
        dataTW,
        instT
    } refT;

    /**
     * @brief structure to hold pointers to all cache levels
     *
     * Caches are implemented as and array of linked lists. Each element of the array is
     * a block in the cache. Each node represents a way for that block.
     * A direct mapped cache is an array of blocks with each element having a single node while a fully associative cache
     * has a single array element and the same number of nodes that would be in the direct mapped array.
     */
    typedef struct
    {
       list ** L1i;     ///< the L1 instruction cache
       list ** L1d;     ///< the L1 data cache
       list ** L2;      ///< the L2 cache
       list * VCL1i;    ///< the L1 instruction victim cache
       list * VCL1d;    ///< the L1 data victim cache
       list * VCL2;     ///< the L2 victim cache
    } allCache;

    /**
     * @brief structure used to hold results of simulation such as times, CPI, cost, etc.
     */
    typedef struct
    {
        ulli    instRefs;       ///< number of instruction references
        ulli    dataReadRef;    ///< number of data read references
        ulli    dataWriteRef;   ///< number of data write references
        ulli    cycleDRead;     ///< number of cycles spent on data reads
        ulli    cycleDWrite;    ///< number of cycles spent on data writes
        ulli    cycleInst;      ///< number of cycles spent on instructions
        ulli    hitL1i;         ///< hit count L1 instruction cache
        ulli    hitL1d;         ///< hit count L1 data cache
        ulli    hitL2;          ///< hit count L2 cache
        ulli    missL1i;        ///< miss count L1 instruction cache
        ulli    missL1d;        ///< miss count L1 data cache
        ulli    missL2;         ///< miss count L2 cache
        ulli    kickoutL1i;     ///< total kickouts L1 instruction cache
        ulli    kickoutL1d;     ///< total kickouts L1 data cache
        ulli    kickoutL2;      ///< total kickouts L2 cache
        ulli    dirtyKickL1i;   ///< total kickouts L1 instruction cache
        ulli    dirtyKickL1d;   ///< total kickouts L1 data cache
        ulli    dirtyKickL2;    ///< total kickouts L2 cache
        ulli    transfersL1i;   ///< number of transfers L1 instruction cache
        ulli    transfersL1d;   ///< number of transfers L1 data cache
        ulli    transfersL2;    ///< number of transfers L2 cache
        ulli    VChitL1i;       ///< victim cache hit count L1 instruction cache
        ulli    VChitL1d;       ///< victim cache hit count L1 data cache
        ulli    VChitL2;        ///< victim cache hit ocunt L2 cache

        /* TODO move these values to printResults, they aren't needed anywhere else */
        ulli    totExecT       ;       ///< total execution time for the simulation
        ulli    totRefs        ;       ///< total number of references = data + instruction
        ulli    dataRefs       ;       ///< number of data references = read + writes
        float   percRefInst    ;       ///< percentage of references that are instructions
        float   percRefDRead   ;       ///< percentage of references that are data reads
        float   percRefDWrite  ;       ///< percentage of references that are data writes
        float   percCycleDR    ;       ///< percentage of cycles that are data reads
        float   percCycleDW    ;       ///< percentage of cycles that are data writes
        float   percCycleInst  ;       ///< percentage of cycles that are instructions
        ulli    idealExecT     ;       ///< ideal execution time
        ulli    idealMisExecT  ;       ///< ideal mis-aligned exectition time
        float   cpi            ;       ///< actual CPI
        float   idealCpi       ;       ///< ideal CPI
        float   idealMisCpi    ;       ///< ideal mis-aligned CPI
        ulli    totalReqL1i    ;       ///< total requests L1 instruction cache
        ulli    totalReqL1d    ;       ///< total requests L1 data cache
        ulli    totalReqL2     ;       ///< total requests L2 cache
        float   hitRateL1i     ;       ///< hit rate percentage L1 instruction cache
        float   hitRateL1d     ;       ///< hit rate percentage L1 data cache
        float   hitRateL2      ;       ///< hit rate percentage L2 cache
        float   missRateL1i    ;       ///< miss rate percentage L1 instruction cache
        float   missRateL1d    ;       ///< miss rate percentage L1 data cache
        float   missRateL2     ;       ///< miss rate percentage L2 cache
    } performance;

    /**
     * @brief prints the current cache contents for all cache levels
     * @param[in] cacheCnfg the configuration setup for the current simulation
     * @param[in] cacheHier structure that contains all cache levels
     * @returns EXIT_SUCCESS or EXIT_FAILURE
     */
    int printCurrCache(memInfo *cacheCnfg, allCache *cacheHier);

    /**
    * @brief Calculates the number of index bits and tag bits for L1 and L2 cache
    *
    * The number of bits can be used in conjunction with bit shifting to calculate the tag and index for
    * a specific address.
    *
    * Each address is broken down into msb - |tag|index|block offset| -  lsb
    * - number of offset bits = log2(byte size of a block in  cache)
    * - number of index bits = log2(# of blocks in the cache / divided by associativity)
    * - number of tags bits = total address bits - # index bits - # offset bits
    *
    * @param[in] mem structure containing cache configuration options, and number of bits for tag and index of each level
    * @returns EXIT_SUCCESS or EXIT_FAILURE
    */
    int calcBits(memInfo *mem);

    /**
     * @brief function to initialize cache levels
     * @param[in] cacheCnfg structure containing cache configuration options
     * @param[in,out] cacheHier pointer to a struct containing doubly linked lists for each memory hierarchy
     * @returns EXIT_SUCCESS or EXIT_FAILURE
     */
    int initCache(memInfo *cacheCnfg, allCache *cacheHier);

    /**
     * @brief function to free the memory allocated for all cache levels
     * @param[in] cacheCnfg structure that contains the configuration settings for each cache level
     * @param[in] cacheHier strucutre that contains pointers to the linked lists for each cache level
     * @returns EXIT_SUCCESS or EXIT_FAILURE
     */
    int deleteCache(memInfo *cacheCnfg, allCache *cacheHier);

#endif // CACHE_H
