/**
 * @file        test_printResults.c
 * @authors     Rane Brown & Brian Douglass
 * @date        03-20-2016
 * @brief       Unit tests for all functions in printResults.h
 */
#include <check.h>
#include <stdlib.h>
#include "printResults.h"
#include "cache.h"

/**
 * @brief unit test for printResults(char *filename)
 */
START_TEST (test_printResults)
{
    // variables
    char filename[]     =       "test_trace";
    int res             =       1;
    memInfo *mem        =       (memInfo*)malloc(sizeof(memInfo));
    mem->L1dSize        =       8192;
    mem->L1dWays        =       2;
    mem->L1dBlock       =       32;
    mem->L1iSize        =       8192;
    mem->L1iWays        =       2;
    mem->L1iBlock       =       32;
    mem->L2Size         =       32768;
    mem->L2Ways         =       1;
    mem->L2Block        =       64;
    mem->readyT         =       50;
    mem->chunkS         =       8;
    mem->chunkT         =       15;
    strcpy(mem->cacheName,"test");
    mem->totalCost      =       100;
    mem->L1TotCost      =       200;
    mem->L1dCost        =       300;
    mem->L1iCost        =       400;
    mem->L2Cost         =       500;
    mem->addrsendT      =       10;
    mem->memoryCost     =       120;
    int nullres         =       0;
    char *nullName      =       NULL;
    int nullres2        =       0;
    memInfo *nullS      =       NULL;
    performance *stats  =   malloc(sizeof(performance));

    // function under test
    res         =       printResults(filename, mem, stats);
    nullres     =       printResults(nullName, mem, stats);
    nullres2    =       printResults(filename, nullS, stats);

    // verify results are as expected
    ck_assert_int_eq(res, EXIT_SUCCESS);
    ck_assert_int_eq(nullres, EXIT_FAILURE);
    ck_assert_int_eq(nullres2, EXIT_FAILURE);

    // free allocated memory
    free(mem);
    free(stats);

}
END_TEST

/**
 * @brief creates a test suite that will contain all unit tests within this file.
 *
 * A test suite is created that will contain all tests within this file.
 * Next, a test case is created for each unit test. The associated unit test is added to that test case.
 * Finally, each test case is added to the suite.
 */
Suite * printResults_suite(void)
{
    // create the test suite
    Suite *s = suite_create("Print Simulation Results");

    // create a test case for each unit test
    TCase *tc_printResults = tcase_create("Core_printResults");

    // add each unit test to its test case
    tcase_add_test(tc_printResults, test_printResults);

    // add each test case to the suite
    suite_add_tcase(s, tc_printResults);

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

    s = printResults_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
