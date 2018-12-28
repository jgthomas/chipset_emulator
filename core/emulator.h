#ifndef EMULATOR_H
#define EMULATOR_H

#include "chipset.h"

chipset *init_chip(int bits, int instruction_count);
int execute(chipset *chip, char *program);
int debug(chipset *chip, char *program);
void delete_chipset(chipset *chip);
int convert_code(char *hex, int bits);

#endif
