/**
 * @file        printResults.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Source file containing functions for printing cache simulator results to a file.
 */
#include "printResults.h"

int printResults(char *filename)
{
    FILE *fp;               // file pointer
    char name[128];         // directory path to write to

    if(filename == NULL)
        return EXIT_FAILURE;

    // concatenate filename to file path
    strcpy(name,"../sim_results/");
    strcat(name, filename);
    strcat(name, ".txt");

    // open file for writing
    fp = fopen(name, "w+");

    // print to file
    fprintf(fp,"------------------------------------------------------------------------------------------\n");
    fprintf(fp, "%20s %30s\n", filename, "Simulation Results");
    fprintf(fp,"------------------------------------------------------------------------------------------\n");

    // close file
    fclose(fp);

    return EXIT_SUCCESS;
}
