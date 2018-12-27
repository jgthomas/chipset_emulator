#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <BCUnit/Basic.h>
#include <BCUnit/BCUnit.h>
#include "emulator_4917.h"


void testANSWER_THREE(void)
{
        char *tests[] = {"03 03 03",
                         "04 04 04 07",
                         "03 03 03 03 03 03 05 05 05",
                         "04 01 01 01",
                         "09 04 05 00 04",
                         "0d 03 00 0a 05 03 07"};

        int num_tests = sizeof(tests) / sizeof(tests[0]);

        int answer = 3;

        init_chip(BASE_CODES);

        for (int i = 0; i < num_tests; i++)
        {
                int result = emulate(tests[i], strlen(tests[i]));
                CU_ASSERT_TRUE(answer == result);
        }
}


/**
 * Each test features an instruction in turn
 *
 * */
void testUSING_ALL_INSTRUCTIONS(void)
{
        char *tests[] = {"03",
                         "04 04 04 01",
                         "04 04 04 04 04 01 05",
                         "03 03 07 01 01 07",
                         "09 03 00 07",
                         "0a 04 07 00 0f",
                         "03 03 03 03 0b 0f 05 05 05 05 09 0f 00"};

        int num_tests = sizeof(tests) / sizeof(tests[0]);

        int answer[] = {1,3,4,2,7,15,4};

        init_chip(BASE_CODES);

        for (int i = 0; i < num_tests; i++)
        {
                int result = emulate(tests[i], strlen(tests[i]));
                CU_ASSERT_TRUE(answer[i] == result);
        }
}


void testMANY_DIFFERENT_INSTRUCTIONS(void)
{
        char *tests[] = {"03 04 01 05 06 07 08 0b 09 0c 0d 09 0a 07",
                         "0d 08 09 08 0f 0a 01 00 0e 02 0a 06 0d 06"};

        int num_tests = sizeof(tests) / sizeof(tests[0]);

        int answer[] = {14,15};

        init_chip(BASE_CODES);

        for (int i = 0; i < num_tests; i++)
        {
                int result = emulate(tests[i], strlen(tests[i]));
                CU_ASSERT_TRUE(answer[i] == result);
        }
}


int main(void)
{
        // test suite
        CU_pSuite suite = NULL;

        // initialize registry
        if (CUE_SUCCESS != CU_initialize_registry())
        {
                return CU_get_error();
        }

        // add suite
        suite = CU_add_suite("Binary heap", 0, 0);
        if (NULL == suite)
        {
                CU_cleanup_registry();
                return CU_get_error();
        }

        // add tests
        if (NULL == CU_add_test(suite, "The answer is three", testANSWER_THREE) ||
            NULL == CU_add_test(suite, "One of each", testUSING_ALL_INSTRUCTIONS) ||
            NULL == CU_add_test(suite, "Many different instruction in one program", testMANY_DIFFERENT_INSTRUCTIONS))
        {
                CU_cleanup_registry();
                return CU_get_error();
        }

        // run tests
        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
        CU_cleanup_registry();
        return CU_get_error();
}
