/**
 * @file        printResults.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Source file containing functions for printing cache simulator results to a file.
 */
#include "printResults.h"

int printResults(char *trace, memInfo *mem, performance *stats)
{
    FILE *fp;               // file pointer
    char name[128];         // directory path to write to
    int numWaysL1 = 0;
    int numWaysL2 = 0;


    if(trace == NULL || mem == NULL)
        PERR("null input");

    // concatenate trace to file path
    strcpy(name,"../sim_results/");
    strcat(name, trace);
    strcat(name,mem->cacheName);
    strcat(name, ".txt");

    // open file for writing
    fp = fopen(name, "w+");
    if(fp == NULL)
        PERR("error opening file");

    if(mem->L1iWays == 0)
        numWaysL1 = mem->L1dSize / mem->L1dBlock;
    else
        numWaysL1 = mem->L1iWays;
    if(mem->L2Ways == 0)
        numWaysL2 = mem->L1dSize / mem->L1dBlock;
    else
        numWaysL2 = mem->L2Ways;

    /* calculate remaining values */
    stats->totExecT      = /*stats->totExecT +*/ stats->cycleDRead + stats->cycleDWrite + stats->cycleInst;  // total execution time for the simulation */
    stats->totRefs       = stats->instRefs + stats->dataReadRef + stats->dataWriteRef;      // total number of references = data + instruction
    stats->dataRefs      = stats->dataReadRef + stats->dataWriteRef;                        // number of data references = read + writes

    stats->percRefInst   = (float) stats->instRefs     / (float) stats->totRefs * 100;      // percentage of references that are instructions
    stats->percRefDRead  = (float) stats->dataReadRef  / (float) stats->totRefs * 100;      // percentage of references that are data reads
    stats->percRefDWrite = (float) stats->dataWriteRef / (float) stats->totRefs * 100;      // percentage of references that are data writes

    stats->percCycleDR   = (float) stats->cycleDRead   / (float) stats->totExecT * 100;     // percentage of cycles that are data reads
    stats->percCycleDW   = (float) stats->cycleDWrite  / (float) stats->totExecT * 100;     // percentage of cycles that are data writes
    stats->percCycleInst = (float) stats->cycleInst    / (float) stats->totExecT * 100;     // percentage of cycles that are instructions

    stats->idealExecT    = stats->dataReadRef + stats->dataWriteRef + 2*stats->instRefs;  // ideal execution time
    stats->idealMisExecT = stats->instRefs + stats->misAlInstRef + stats->misAlDReadRef + stats->misAlDWriteRef;    // ideal mis-aligned execution time

    stats->cpi           = (float) (stats->totExecT)      / (float) stats->instRefs;      // actual CPI
    stats->idealCpi      = (float) (stats->idealExecT)    / (float) stats->instRefs;      // ideal CPI
    stats->idealMisCpi   = (float) (stats->idealMisExecT) / (float) stats->instRefs;      // ideal mis-aligned CPI

    stats->totalReqL1i = stats->hitL1i + stats->missL1i;  // total requests L1 instruction cache
    stats->totalReqL1d = stats->hitL1d + stats->missL1d;  // total requests L1 data cache
    stats->totalReqL2  = stats->hitL2 + stats->missL2;    // total requests L2 cache

    stats->hitRateL1i     = (float) stats->hitL1i / (float) stats->totalReqL1i * 100;     // hit rate percentage L1 instruction cache
    stats->hitRateL1d     = (float) stats->hitL1d / (float) stats->totalReqL1d * 100;     // hit rate percentage L1 data cache
    stats->hitRateL2      = (float) stats->hitL2  / (float) stats->totalReqL2 * 100;       // hit rate percentage L2 cache

    stats->missRateL1i    = 100 - stats->hitRateL1i;       // miss rate percentage L1 instruction cache
    stats->missRateL1d    = 100 - stats->hitRateL1d;       // miss rate percentage L1 data cache
    stats->missRateL2     = 100 - stats->hitRateL2;       // miss rate percentage L2 cache

    stats->transfersL1i   = stats->missL1i - stats->VChitL1i;
    stats->transfersL1d   = stats->missL1d - stats->VChitL1d;
    stats->transfersL2    = stats->missL2 - stats->VChitL2;

    // print to file
    fprintf( fp, "-----------------------------------------------------------------------------------------------\n");
    fprintf( fp, "%20s.%s %30s\n", trace,mem->cacheName, "Simulation Results");
    fprintf( fp, "-----------------------------------------------------------------------------------------------\n");
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Memory System Information");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%20s %20s %20s %20s\n", "hierarchy", "size", "ways", "block size");
    fprintf( fp, "%20s %20s %20s %20s\n", "---------", "----", "----", "----------");
    fprintf( fp, "%20s %20d %20d %20d\n", "L1 data",        mem->L1dSize, numWaysL1, mem->L1dBlock);
    fprintf( fp, "%20s %20d %20d %20d\n", "L1 instruction", mem->L1iSize, numWaysL1, mem->L1iBlock);
    fprintf( fp, "%20s %20d %20d %20d\n", "L2 cache",       mem->L2Size, numWaysL2, mem->L2Block);
    fprintf( fp, "\n");
    fprintf( fp, "%20s %20s %20s %20s\n", "hierarchy", "ready time", "chunk size", "chunk time");
    fprintf( fp, "%20s %20s %20s %20s\n", "---------", "----------", "----------", "----------");
    fprintf( fp, "%20s %20d %20d %20d\n", "Main memory",    mem->readyT, mem->chunkS, mem->chunkT);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Overall Performance");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%40s %30llu\n", "Execution time",         stats->totExecT);
    fprintf( fp, "%40s %30llu\n", "Total references",       stats->totRefs);
    fprintf( fp, "%40s %30llu\n", "Instruction references", stats->instRefs);
    fprintf( fp, "%40s %30llu\n", "Data references",        stats->dataRefs);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Number of references by type");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%25s %25s %25s\n", "type", "count", "percentage");
    fprintf( fp, "%25s %25s %25s\n", "----", "-----", "----------");
    fprintf( fp, "%25s %25llu %25.2f\n", "reads",       stats->dataReadRef, stats->percRefDRead);
    fprintf( fp, "%25s %25llu %25.2f\n", "writes",      stats->dataWriteRef, stats->percRefDWrite);
    fprintf( fp, "%25s %25llu %25.2f\n", "instruction", stats->instRefs, stats->percRefInst);
    fprintf( fp, "%25s %25s %25s\n", "", "--------------", "---------------");
    fprintf( fp, "%25s %25llu %25.2f\n", "total",       stats->totRefs, 100.00);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Total cycles for activities");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%25s %25s %25s\n", "type", "count", "percentage");
    fprintf( fp, "%25s %25s %25s\n", "----", "-----", "----------");
    fprintf( fp, "%25s %25llu %25.2f\n", "reads",       stats->cycleDRead, stats->percCycleDR);
    fprintf( fp, "%25s %25llu %25.2f\n", "writes",      stats->cycleDWrite, stats->percCycleDW);
    fprintf( fp, "%25s %25llu %25.2f\n", "instruction", stats->cycleInst, stats->percCycleInst);
    fprintf( fp, "%25s %25s %25s\n", "", "---------------", "---------------");
    fprintf( fp, "%25s %25llu %25.2f\n", "total",       stats->cycleInst+stats->cycleDRead+stats->cycleDWrite, 100.00);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "CPI and ideal values");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%25s %25s %25s\n", "type", "execution time", "CPI");
    fprintf( fp, "%25s %25s %25s\n", "----", "--------------", "---");
    fprintf( fp, "%25s %25llu %25.1f\n", "actual",            stats->totExecT, stats->cpi);
    fprintf( fp, "%25s %25llu %25.1f\n", "ideal",             stats->idealExecT, stats->idealCpi);
    fprintf( fp, "%25s %25llu %25.1f\n", "ideal mis-aligned", stats->idealMisExecT, stats->idealMisCpi);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Performance by hierarchy");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%20s %20s %20s %20s\n", "value", "L1i", "L1d", "L2");
    fprintf( fp, "%20s %20s %20s %20s\n", "-----", "----", "----", "----");
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "hit count",      stats->hitL1i, stats->hitL1d, stats->hitL2);
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "miss count",     stats->missL1i, stats->missL1d, stats->missL2);
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "total requests", stats->totalReqL1i, stats->totalReqL1d, stats->totalReqL2);
    fprintf( fp, "%20s %20.2f %20.2f %20.2f\n", "hit rate",       stats->hitRateL1i, stats->hitRateL1d, stats->hitRateL2);
    fprintf( fp, "%20s %20.2f %20.2f %20.2f\n", "miss rate",      stats->missRateL1i, stats->missRateL1d, stats->missRateL2);
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "kickouts",       stats->kickoutL1i, stats->kickoutL1d, stats->kickoutL2);
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "dirty kickouts", stats->dirtyKickL1i, stats->dirtyKickL1d, stats->dirtyKickL2);
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "transfers",      stats->transfersL1i, stats->transfersL1d, stats->transfersL2);
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "VC hit count",   stats->VChitL1i, stats->VChitL1d, stats->VChitL2);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Memory Cost");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%40s %30s\n", "hierarchy", "cost");
    fprintf( fp, "%40s %30s\n", "---------", "----");
    fprintf( fp, "%40s %30d\n", "L1",          mem->L1TotCost);
    fprintf( fp, "%40s %30d\n", "L2",          mem->L2Cost);
    fprintf( fp, "%40s %30d\n", "Main memory", mem->memoryCost);
    fprintf( fp, "%40s %30s\n", "", "---------------" );
    fprintf( fp, "%40s %30d\n", "Total",       mem->totalCost);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    // close file
    if(fclose(fp))
        PERR("error closing file");
    else
        return EXIT_SUCCESS;
}
