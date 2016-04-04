/**
 * @file        readTrace.h
 * @authors     Rane Brown & Brian Douglass
 * @date        03-23-2016
 * @brief       Header file with function prototypes for reading a trace from stdin
 */
#ifndef READ_TRACE_H
    #define READ_TRACE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/select.h>
    #include <errno.h>

    /**
     * @brief reads a single trace line from stdin
     * @param[out] op type of operation - read or write or instruction
     * @param[out] addr memory address
     * @param[out] numBytes the number of bytes referenced by the request
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int readTrace(char *op, unsigned long long int *addr, unsigned int *numBytes);

#endif // READ_TRACE_H
