/**
 * @file        cache.h
 * @authors     Rane Brown & Brian Douglass
 * @date        04-01-2016
 * @brief       Header file with function prototypes and structs used for cache operations
 */
#ifndef DIRECT_MAPPED_H
    #define DIRECT_MAPPED_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "config.h"

    /**
     * @typedef ulli
     * @brief typedef for an unsigned long long int because that is too much to write
     */
    typedef unsigned long long int ulli;

    /**
     * @struct block
     * @brief structure used to represent a cache block
     */
    typedef struct
    {
        int     dirty;       ///< indicates whether a write has occurred
        int     valid;       ///< indicates if the data in cache block is 1 = valid, 0 = garbage
        ulli    tag;         ///< maps a specific memory address to a block - multiple addresses map to same block
    } block;

    /**
     * @struct performance
     * @brief structure used to hold results of simulation such as times, CPI, cost, etc.
     */
    typedef struct
    {
        ulli    totExecT;       ///< total execution time for the simulation
        ulli    totRefs;        ///< total number of references = data + instruction
        ulli    instRefs;       ///< number of instruction references
        ulli    dataRefs;       ///< number of data references = read + writes
        ulli    dataReads;      ///< number of data reads
        ulli    dataWrites;     ///< number of data writes
        float   percRefInst;    ///< percentage of references that are instructions
        float   percRefDRead;   ///< percentage of references that are data reads
        float   percRefDWrite;  ///< percentage of references that are data writes
        ulli    cycleDRead;     ///< number of cycles spent on data reads
        ulli    cycleDWrite;    ///< number of cycles spent on data writes
        ulli    cycleInst;      ///< number of cycles spent on instructions
        float   percCycleDR;    ///< percentage of cycles that are data reads
        float   percCycleDW;    ///< percentage of cycles that are data writes
        float   percCycleInst;  ///< percentage of cycles that are instructions
        ulli    idealExecT;     ///< ideal execution time
        ulli    idealMisExecT;  ///< ideal mis-aligned exectition time
        float   cpi;            ///< actual CPI
        float   idealCpi;       ///< ideal CPI
        float   idealMisCpi;    ///< ideal mis-aligned CPI
        ulli    hitL1i;         ///< hit count L1 instruction cache
        ulli    hitL1d;         ///< hit count L1 data cache
        ulli    hitL2;          ///< hit count L2 cache
        ulli    missL1i;        ///< miss count L1 instruction cache
        ulli    missL1d;        ///< miss count L1 data cache
        ulli    missL2;         ///< miss count L2 cache
        ulli    totalReqL1i;    ///< total requests L1 instruction cache
        ulli    totalReqL1d;    ///< total requests L1 data cache
        ulli    totalReqL2;     ///< total requests L2 cache
        float   hitRateL1i;     ///< hit rate percentage L1 instruction cache
        float   hitRateL1d;     ///< hit rate percentage L1 data cache
        float   hitRateL2;      ///< hit rate percentage L2 cache
        float   missRateL1i;    ///< miss rate percentage L1 instruction cache
        float   missRateL1d;    ///< miss rate percentage L1 data cache
        float   missRateL2;     ///< miss rate percentage L2 cache
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
    } performance;

#endif // DIRECT_MAPPED_H
