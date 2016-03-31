/**
 * @file        printResults.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Source file containing functions for printing cache simulator results to a file.
 */
#include "printResults.h"

int printResults(char *trace, memInfo *mem)
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
    fprintf( fp, "%40s %30d\n", "Execution time", 8384);
    fprintf( fp, "%40s %30d\n", "Total references", 384);
    fprintf( fp, "%40s %30d\n", "Instruction references", 84);
    fprintf( fp, "%40s %30d\n", "Data references", 8744);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Number of references by type");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%25s %25s %25s\n", "type", "count", "percentage");
    fprintf( fp, "%25s %25s %25s\n", "----", "-----", "----------");
    fprintf( fp, "%25s %25d %25.2f\n", "reads", 23, 87.6);
    fprintf( fp, "%25s %25d %25.2f\n", "writes", 43, 88.8);
    fprintf( fp, "%25s %25d %25.2f\n", "instruction", 89848984, 99.99);
    fprintf( fp, "%25s %25s %25s\n", "", "--------------", "---------------");
    fprintf( fp, "%25s %25d %25.2f\n", "total", 89848984, 100.00);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Total cycles for activities");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%25s %25s %25s\n", "type", "count", "percentage");
    fprintf( fp, "%25s %25s %25s\n", "----", "-----", "----------");
    fprintf( fp, "%25s %25d %25.2f\n", "reads", 23, 87.6);
    fprintf( fp, "%25s %25d %25.2f\n", "writes", 43, 88.8);
    fprintf( fp, "%25s %25d %25.2f\n", "instruction", 89848984, 99.99);
    fprintf( fp, "%25s %25s %25s\n", "", "---------------", "---------------");
    fprintf( fp, "%25s %25d %25.2f\n", "total", 89848984, 100.00);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "CPI and ideal values");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%25s %25s %25s\n", "type", "execution time", "CPI");
    fprintf( fp, "%25s %25s %25s\n", "----", "--------------", "---");
    fprintf( fp, "%25s %25d %25.1f\n", "actual", 99999999, 87.6);
    fprintf( fp, "%25s %25d %25.1f\n", "ideal", 758394, 2.5);
    fprintf( fp, "%25s %25d %25.1f\n", "ideal mis-aligned", 758394, 7.8);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Performance by hierarchy");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%20s %20s %20s %20s\n", "value", "L1i", "L1d", "L2");
    fprintf( fp, "%20s %20s %20s %20s\n", "-----", "----", "----", "----");
    fprintf( fp, "%20s %20d %20d %20d\n", "hit count", 89, 88, 77);
    fprintf( fp, "%20s %20d %20d %20d\n", "miss count", 89, 88, 77);
    fprintf( fp, "%20s %20d %20d %20d\n", "total requests", 89, 88, 77);
    fprintf( fp, "%20s %20.2f %20.2f %20.2f\n", "hit rate", 89.2, 88.8, 77.8);
    fprintf( fp, "%20s %20.2f %20.2f %20.2f\n", "miss rate", 89.2, 88.8, 77.8);
    fprintf( fp, "%20s %20d %20d %20d\n", "kickouts", 89, 88, 77);
    fprintf( fp, "%20s %20d %20d %20d\n", "dirty kickouts", 89, 88, 77);
    fprintf( fp, "%20s %20d %20d %20d\n", "transfers", 89, 88, 77);
    fprintf( fp, "%20s %20d %20d %20d\n", "VC hit count", 89, 88, 77);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    fprintf( fp, "%60s\n", "Memory Cost");
    fprintf( fp, "%90s\n", "-------------------------------------------------------------------------------------");
    fprintf( fp, "%40s %30s\n", "hierarchy", "cost");
    fprintf( fp, "%40s %30s\n", "---------", "----");
    fprintf( fp, "%40s %30d\n", "L1", 100);
    fprintf( fp, "%40s %30d\n", "L2", 834);
    fprintf( fp, "%40s %30d\n", "Main memory", 129);
    fprintf( fp, "%40s %30s\n", "", "---------------" );
    fprintf( fp, "%40s %30d\n", "Total", 129);
    fprintf( fp, "\n");
    fprintf( fp, "\n");

    // close file
    int close = fclose(fp);
    if(close == 0)
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}
