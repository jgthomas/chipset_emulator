#include <stdio.h>
#include "chipset.h"
#include "instructions.h"
#include "emulator.h"


int main(void)
{
        int bits = 4;
        int instructions = 16;
        char *program = "03 03 03 04 04 04 04 07";

        chipset *chip = init_chipset(bits);
        load_instructions(chip, instructions);

        printf("result: %d\n", execute(chip, program));

        delete_chipset(chip);
}
