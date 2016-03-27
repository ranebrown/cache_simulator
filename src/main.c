/**
 * @file        main.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-18-2016
 * @brief       Main file for cache simulator project.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printResults.h"
#include "readTrace.h"

int main(int argc, char *argv[])
{
    FILE *config;                       /// file pointer to configuration file
    char inStr[20];                     /// the line read in from configuration file
    char op;                            /// type of operation - read or write or instruction
    unsigned long long int addr;        /// memory address
    unsigned int bs;                    /// byte size - number of bytes referenced by request
    int res = 0;                        /// result of trace read

    (argc == 2) ? (config = fopen(argv[1],"r"))
                : (config = fopen("default","r"));
    fscanf(config, "%s", inStr);
    printf("-- %s --\n",inStr);

    while(res == 0)
    {
        res = readTrace(&op, &addr, &bs);
        printf("%c %llx %d\n" ,op ,addr ,bs);

    }

    return EXIT_SUCCESS;
}
