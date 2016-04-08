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

    if(trace == NULL || mem == NULL)
        return EXIT_FAILURE;

    // concatenate trace to file path
    strcpy(name,"../sim_results/");
    strcat(name, trace);
    strcat(name, ".txt");

    // open file for writing
    fp = fopen(name, "w+");
    if(fp == NULL)
    {
        perror("error opening file to print simulation results");
        return EXIT_FAILURE;
    }

    /* calculate remaining values */
    /* ulli    totExecT       =   0;       // total execution time for the simulation */
    /* ulli    totRefs        =   0;       // total number of references = data + instruction */
    /* ulli    dataRefs       =   0;       // number of data references = read + writes */
    /* float   percRefInst    =   0;       // percentage of references that are instructions */
    /* float   percRefDRead   =   0;       // percentage of references that are data reads */
    /* float   percRefDWrite  =   0;       // percentage of references that are data writes */
    /* float   percCycleDR    =   0;       // percentage of cycles that are data reads */
    /* float   percCycleDW    =   0;       // percentage of cycles that are data writes */
    /* float   percCycleInst  =   0;       // percentage of cycles that are instructions */
    /* ulli    idealExecT     =   0;       // ideal execution time */
    /* ulli    idealMisExecT  =   0;       // ideal mis-aligned exectition time */
    /* float   cpi            =   0;       // actual CPI */
    /* float   idealCpi       =   0;       // ideal CPI */
    /* float   idealMisCpi    =   0;       // ideal mis-aligned CPI */
    /* ulli    totalReqL1i    =   0;       // total requests L1 instruction cache */
    /* ulli    totalReqL1d    =   0;       // total requests L1 data cache */
    /* ulli    totalReqL2     =   0;       // total requests L2 cache */
    /* float   hitRateL1i     =   0;       // hit rate percentage L1 instruction cache */
    /* float   hitRateL1d     =   0;       // hit rate percentage L1 data cache */
    /* float   hitRateL2      =   0;       // hit rate percentage L2 cache */
    /* float   missRateL1i    =   0;       // miss rate percentage L1 instruction cache */
    /* float   missRateL1d    =   0;       // miss rate percentage L1 data cache */
    /* float   missRateL2     =   0;       // miss rate percentage L2 cache */

    // print to file
    fprintf( fp, "-----------------------------------------------------------------------------------------------\n");
    fprintf( fp, "%20s %40s\n", trace, "Simulation Results");
    fprintf( fp, "-----------------------------------------------------------------------------------------------\n");
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Memory System Information");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%20s %20s %20s %20s\n", "hierarchy", "size", "ways", "block size");
    fprintf( fp, "%20s %20s %20s %20s\n", "---------", "----", "----", "----------");
    fprintf( fp, "%20s %20d %20d %20d\n", "L1 data", mem->L1dSize, mem->L1dWays, mem->L1dBlock);
    fprintf( fp, "%20s %20d %20d %20d\n", "L1 instruction", mem->L1iSize, mem->L1iWays, mem->L1iBlock);
    fprintf( fp, "%20s %20d %20d %20d\n", "L2 cache", mem->L2Size, mem->L2Ways, mem->L2Block);
    fprintf( fp, "\n");
    fprintf( fp, "%20s %20s %20s %20s\n", "hierarchy", "ready time", "chunk size", "chunk time");
    fprintf( fp, "%20s %20s %20s %20s\n", "---------", "----------", "----------", "----------");
    fprintf( fp, "%20s %20d %20d %20d\n", "Main memory", mem->readyT, mem->chunkS, mem->chunkT);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    // TODO - correct data types for below items - replace with variables
    fprintf( fp, "%60s\n", "Overall Performance");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%40s %30llu\n", "Execution time", stats->totExecT);
    fprintf( fp, "%40s %30llu\n", "Total references", stats->totRefs);
    fprintf( fp, "%40s %30llu\n", "Instruction references", stats->instRefs);
    fprintf( fp, "%40s %30llu\n", "Data references", stats->dataRefs);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Number of references by type");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%25s %25s %25s\n", "type", "count", "percentage");
    fprintf( fp, "%25s %25s %25s\n", "----", "-----", "----------");
    fprintf( fp, "%25s %25llu %25.2f\n", "reads", stats->dataReadRef, stats->percRefDRead);
    fprintf( fp, "%25s %25llu %25.2f\n", "writes", stats->dataWriteRef, stats->percRefDWrite);
    fprintf( fp, "%25s %25llu %25.2f\n", "instruction", stats->instRefs, stats->percRefInst);
    fprintf( fp, "%25s %25s %25s\n", "", "--------------", "---------------");
    fprintf( fp, "%25s %25llu %25.2f\n", "total", stats->totRefs, 100.00);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Total cycles for activities");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%25s %25s %25s\n", "type", "count", "percentage");
    fprintf( fp, "%25s %25s %25s\n", "----", "-----", "----------");
    fprintf( fp, "%25s %25llu %25.2f\n", "reads", stats->cycleDRead, stats->percCycleDR);
    fprintf( fp, "%25s %25llu %25.2f\n", "writes", stats->cycleDWrite, stats->percCycleDW);
    fprintf( fp, "%25s %25llu %25.2f\n", "instruction", stats->cycleInst, stats->percCycleInst);
    fprintf( fp, "%25s %25s %25s\n", "", "---------------", "---------------");
    fprintf( fp, "%25s %25llu %25.2f\n", "total", stats->cycleInst+stats->cycleDRead+stats->cycleDWrite, 100.00);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "CPI and ideal values");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%25s %25s %25s\n", "type", "execution time", "CPI");
    fprintf( fp, "%25s %25s %25s\n", "----", "--------------", "---");
    fprintf( fp, "%25s %25llu %25.1f\n", "actual", stats->totExecT, stats->cpi);
    fprintf( fp, "%25s %25llu %25.1f\n", "ideal", stats->idealExecT, stats->idealCpi);
    fprintf( fp, "%25s %25llu %25.1f\n", "ideal mis-aligned", stats->idealMisExecT, stats->idealMisCpi);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Performance by hierarchy");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%20s %20s %20s %20s\n", "value", "L1i", "L1d", "L2");
    fprintf( fp, "%20s %20s %20s %20s\n", "-----", "----", "----", "----");
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "hit count", stats->hitL1i, stats->hitL1d, stats->hitL2);
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "miss count", stats->missL1i, stats->missL1d, stats->missL2);
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "total requests", stats->totalReqL1i, stats->totalReqL1d, stats->totalReqL2);
    fprintf( fp, "%20s %20.2f %20.2f %20.2f\n", "hit rate", stats->hitRateL1i, stats->hitRateL1d, stats->hitRateL2);
    fprintf( fp, "%20s %20.2f %20.2f %20.2f\n", "miss rate", stats->missRateL1i, stats->missRateL1d, stats->missRateL2);
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "kickouts", stats->kickoutL1i, stats->kickoutL1d, stats->kickoutL2);
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "dirty kickouts", stats->dirtyKickL1i, stats->dirtyKickL1d, stats->dirtyKickL2);
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "transfers", stats->transfersL1i, stats->transfersL1d, stats->transfersL2);
    fprintf( fp, "%20s %20llu %20llu %20llu\n", "VC hit count", stats->VChitL1i, stats->VChitL1d, stats->VChitL2);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Memory Cost");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%40s %30s\n", "hierarchy", "cost");
    fprintf( fp, "%40s %30s\n", "---------", "----");
    fprintf( fp, "%40s %30d\n", "L1", mem->L1TotCost);
    fprintf( fp, "%40s %30d\n", "L2", mem->L2Cost);
    fprintf( fp, "%40s %30d\n", "Main memory", mem->memoryCost);
    fprintf( fp, "%40s %30s\n", "", "---------------" );
    fprintf( fp, "%40s %30d\n", "Total", mem->totalCost);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    // close file
    int close = fclose(fp);
    if(close == 0)
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}
