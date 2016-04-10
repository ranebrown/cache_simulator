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

    #define HIT 0               ///< used as a return value for a cache hit
    #define MISS 1              ///< used as a return value for a cache miss
    #define L1_OFFSET 5         ///< L1 is 32 bytes i.e. 2^5
    #define L2_OFFSET 6         ///< L2 is 64 bytes i.e. 2^6
    #define L1_HIT_TIME 1       ///< number of cycles to return an L1 hit
    #define L1_MISS_TIME 1      ///< number of cycles to determine an L1 request is a miss and make request to L2
    #define L2_HIT_TIME 20      ///< number of cycles to return an L2 hit
    #define L2_MISS_TIME 180    ///< number of cycles to determine an L2 request is a miss and make request to main memory
    #define CLEAN 0             ///< dirty bit status
    #define DIRTY 1             ///< dirty bit status

    typedef unsigned long long int ulli;    ///< shorten long type
    typedef unsigned int ui;                ///< maintain same format as ulli

    /**
     * @brief structure to hold pointers to all cache levels
     */
    typedef struct
    {
       list ** L1i;
       list ** L1d;
       list ** L2;
       list ** VCL1i;
       list ** VCL1d;
       list ** VCL2;
    } allCache;

    /**
     * @brief function to initialize cache levels
     * @param[in] cacheCnfg structure containing cache configuration options
     * @param[in,out] cacheHier pointer to a struct containing doubly linked lists for each memory hierarchy
     * @returns EXIT_SUCCESS or EXIT_FAILURE
     */
    int initCache(memInfo *cacheCnfg, allCache *cacheHier);

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
    * @param[in] mem structure containing cache configuration options
    * @param[out] bitsIndexL1 the number of index bits for L1 cache
    * @param[out] bitsTagL1 the number of tag bits for L1 cache
    * @param[out] bitsIndexL2 the number of index bits for L2 cache
    * @param[out] bitsTagL2 the nubmer of tag bits for L2 cache
    * @returns EXIT_SUCCESS or EXIT_FAILURE
    */
    int calcBits(memInfo *mem, int *bitsIndexL1, int *bitsTagL1, int *bitsIndexL2, int *bitsTagL2);

#endif // CACHE_H
