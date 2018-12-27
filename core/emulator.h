#ifndef EMULATOR_H
#define EMULATOR_H

#include "chipset.h"

chipset *init_chipset(int bits);
void load_instructions(chipset *chip, int count);
void load_program(chipset *chip, char *program);
void execute_program(chipset *chip);

#endif
