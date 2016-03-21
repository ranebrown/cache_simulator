/**
 * @file        printResults.h
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Header file with function prototypes for printing the cache simulation results to a file.
 */
#ifndef PRINT_RESULTS_H
    #define PRINT_RESULTS_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    /**
     * @brief prints the results of the simulation to a file
     * @param[in] filename string containing the name of the file to create
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int printResults(char *filename);

#endif // PRINT_RESULTS_H
