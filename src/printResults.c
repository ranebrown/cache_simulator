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

    if(trace == NULL)
        return EXIT_FAILURE;

    // concatenate trace to file path
    strcpy(name,"../sim_results/");
    strcat(name, trace);
    strcat(name, ".txt");

    // open file for writing
    fp = fopen(name, "w+");

    // print to file
    fprintf( fp, "------------------------------------------------------------------------------------------\n");
    fprintf( fp, "%20s %30s\n", trace, "Simulation Results");
    fprintf( fp, "------------------------------------------------------------------------------------------\n");
    fprintf( fp, "\n");
    fprintf( fp, "%60s\n","Memory System Information");
    fprintf( fp, "%60s\n","-------------------------");
    fprintf( fp, "%20s %20s %20s %20s\n", "hierarchy", "size", "ways", "block size");
    fprintf( fp, "%20s %20s %20s %20s\n", "---------", "----", "----", "----------");
    fprintf( fp, "%20s %20d %20d %20d\n", "L1 data", mem->L1dSize, mem->L1dWays, mem->L1dBlock);
    fprintf( fp, "%20s %20d %20d %20d\n", "L1 instruction", mem->L1iSize, mem->L1iWays, mem->L1iBlock);
    fprintf( fp, "%20s %20d %20d %20d\n", "L2 cache", mem->L2Size, mem->L2Ways, mem->L2Block);
    fprintf( fp, "\n");
    fprintf( fp, "%20s %20s %20s %20s\n", "hierarchy", "ready time", "chunk size", "chunk time");
    fprintf( fp, "%20s %20s %20s %20s\n", "---------", "----------", "----------", "----------");
    fprintf( fp, "%20s %20d %20d %20d\n", "Main memory", mem->readyT, mem->chunkS, mem->chunkT);

    // close file
    fclose(fp);

    return EXIT_SUCCESS;
}
