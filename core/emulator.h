#ifndef EMULATOR_H
#define EMULATOR_H

#include "chipset.h"

//chipset *init_chipset(int bits);
chipset *init_chip(int bits, int instruction_count);
//void load_instructions(chipset *chip, int count);
//void load_program(chipset *chip, char *program);
int execute(chipset *chip, char *program);
//void execute_program(chipset *chip);
int debug(chipset *chip, char *program);
void delete_chipset(chipset *chip);

#endif
