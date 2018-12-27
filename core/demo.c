#include <stdio.h>
#include "chipset.h"
#include "instructions.h"
#include "emulator.h"


int main(void)
{
        int bits = 4;
        int instructions = 16;
        char *program = "03 03 03 04 04 04 04 07";

        chipset *chip = init_chip(bits, instructions);

        printf("result: %d\n", execute(chip, program));
        printf("result: %d\n", debug(chip, program));

        delete_chipset(chip);
}
