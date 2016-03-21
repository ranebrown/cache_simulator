/**
 * @file        printResults.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Source file containing functions for printing cache simulator results to a file.
 */
#include "printResults.h"

int printResults(char *filename)
{
    FILE *fp;                                   // file pointer
    char name[]     =   "../sim_results/";      // directory path to write to

    // concatenate filename to file path
    strcat(name, filename);

    // open file for writing
    fp = fopen(name, "w+");

    // print to file
    fprintf(fp, "%10s %10s\n", name, "Simulation Results");

    // close file
    fclose(fp);

    return EXIT_SUCCESS;
}
