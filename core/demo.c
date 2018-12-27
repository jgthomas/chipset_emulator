#include <stdio.h>
#include "chipset.h"
#include "instructions.h"
#include "emulator.h"


int main(void)
{
        int bits = 4;
        int instructions = 16;
        char *program = "03 03 03 04 04 04 04";

        chipset *chip = init_chipset(bits);

        load_instructions(chip, instructions);

        load_program(chip, program);

        print_memory(chip);

        execute_program(chip);

        printf("result %d\n", chip->R0);

        delete_chipset(chip);
}
