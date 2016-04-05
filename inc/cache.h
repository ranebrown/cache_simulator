/**
 * @file        directMapped.h
 * @authors     Rane Brown & Brian Douglass
 * @date        04-01-2016
 * @brief       Header file with function prototypes and structs related to a direct mapped cache
 */
#ifndef DIRECT_MAPPED_H
    #define DIRECT_MAPPED_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "config.h"

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
        ulli    totExecT;      ///< total execution time for the simulation
        ulli    totRefs;       ///< total number of references = data + instruction
        ulli    instRefs;      ///< number of instruction references
        ulli    dataRefs;      ///< number of data references = read + writes
        ulli    readCount;     ///< number of data reads
        ulli    writeCount;    ///< number of data writes
        float   percInst;      ///< percentage of references that are instructions
        float   percDRead;     ///< percentage of references that are data reads
        float   percDWrite;    ///< percentage of references that are data writes
    } performance;

    /**
     * @typedef ulli
     * @brief typedef for an unsigned long long int because its a pain to write that so often
     */
    typedef unsigned long long int ulli;

#endif // DIRECT_MAPPED_H
