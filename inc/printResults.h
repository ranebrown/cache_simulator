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
    #include <errno.h>
    #include "config.h"
    #include "cache.h"
    #include "common.h"

    /**
     * @brief prints the results of the simulation to a file
     * @param[in] trace string containing the name of the currently running trace
     * @param[in] mem struct containing memory configuration parameters
     * @param[in] stats struct containing statistics about the cache simulation
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int printResults(char *trace, memInfo *mem, performance *stats);

#endif // PRINT_RESULTS_H
