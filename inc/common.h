/**
 * @file        common.h
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Header file to contain items that are used by all files to avoid circular dependencies
 */
#ifndef COMMON_H
    #define COMMON_H

    /**
     * @brief macro to print an error message to stderr, uses var args to accept printf format input, returns EXIT_FAILURE
     */
    #define PERR(M, ...) do {fprintf(stderr, "ERROR: --- FILE:%s LINE:%d FUNCTION:%s --- " M "\n", \
            __FILE__, __LINE__, __func__,  ##__VA_ARGS__); return EXIT_FAILURE;} while(0)

    typedef enum
    {
        false,
        true
    } bool; 

#endif // COMMON_H

