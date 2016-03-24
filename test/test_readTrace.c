/**
 * @file        test_readTrace.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-23-2016
 * @brief       Unit tests for all functions in readTrace.h
 */
#include <check.h>
#include <stdlib.h>
#include "readTrace.h"

/**
 * @brief unit test for int readTrace(char *op, unsigned long long int *addr, unsigned int *bs)
 */
START_TEST (test_readTrace)
{
    char op;                            /// type of operation - read or write or instruction
    unsigned long long int addr;        /// memory address
    unsigned int bs;                    /// byte size - number of bytes referenced by request
    int res = 1;                        /// result of read

    // expected results
    char tr_op[10]                          =   {'I', 'I', 'W', 'I', 'W', 'I', 'I', 'W', 'I', 'W'};
    unsigned long long int tr_addr[10]      =   {
                                                    0x7f81ce2206b0,
                                                    0x7f81ce2206b3,
                                                    0x7fff5a8487d8,
                                                    0x7f81ce224010,
                                                    0x7fff5a8487d0,
                                                    0x7f81ce224011,
                                                    0x7f81ce224014,
                                                    0x7fff5a8487c8,
                                                    0x7f81ce224016,
                                                    0x7fff5a8487c0
                                                };
    unsigned int tr_bs[10]                  =   {3, 5, 8, 1, 8, 3, 2, 8, 2, 8};


    // call function and verify results are correct
    for(int i=0; i<10; i++)
    {
        res = readTrace(&op, &addr, &bs);
        if(op != tr_op[i])
            ck_abort_msg("\noperation incorrect\n");
        if(addr != tr_addr[i])
            ck_abort_msg("\naddress incorrect\n");
        if(bs != tr_bs[i])
            ck_abort_msg("\nbyte size incorrect\n");
    }
}
END_TEST

/**
 * @brief creates a test suite that will contain all unit tests within this file.
 *
 * A test suite is created that will contain all tests within this file.
 * Next, a test case is created for each unit test. The associated unit test is added to that test case.
 * Finally, each test case is added to the suite.
 */
Suite * readTrace_suite(void)
{
    // create the test suite
    Suite *s = suite_create("Read Trace");

    // create a test case for each unit test
    TCase *tc_readTrace = tcase_create("Core_readTrace");

    // add each unit test to its test case
    tcase_add_test(tc_readTrace, test_readTrace);

    // add each test case to the suite
    suite_add_tcase(s, tc_readTrace);

    return s;
}

/**
 * @brief main section for printResults unit tests - should not be modified except for the name
 *  of the function used for creating the test suite
 */
int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = readTrace_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
