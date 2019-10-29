#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "chipset.h"
#include "instructions.h"
#include "emulator.h"


void test_answer_three(void **state)
{
        char *tests[] = {"03 03 03 00",
                         "04 04 04 07 00",
                         "03 03 03 03 03 03 05 05 05 00",
                         "04 01 01 01 00",
                         "09 04 05 00 04 00",
                         "0d 03 00 0a 05 03 07 00"};

        int num_tests = sizeof(tests) / sizeof(tests[0]);

        int answer = 3;

        chipset *chip = init_chip(4, 16);

        for (int i = 0; i < num_tests; i++)
        {
                int result = execute(chip, tests[i]);
                assert_int_equal(answer, result);
        }

        delete_chipset(chip);
}


void test_many_different_instructions(void **state)
{
        char *tests[] = {"03 04 01 05 06 07 08 0b 09 0c 0d 09 0a 07 00",
                         "0d 08 09 08 0f 0a 01 00 0e 02 0a 06 0d 06 00"};

        int num_tests = sizeof(tests) / sizeof(tests[0]);

        int answer[] = {14,15};

        chipset *chip = init_chip(4, 16);

        for (int i = 0; i < num_tests; i++)
        {
                int result = execute(chip, tests[i]);
                assert_int_equal(answer[i], result);
        }

        delete_chipset(chip);
}


int main(void)
{
        const struct CMUnitTest tests[] =
        {
            cmocka_unit_test(test_answer_three),
            cmocka_unit_test(test_many_different_instructions),
        };

        return cmocka_run_group_tests(tests, NULL, NULL);
}
