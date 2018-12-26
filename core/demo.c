#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "chipset.h"

chipset *init_chipset(int bits);
void delete_chipset(chipset *chip);
void init_registers(chipset *chip);
int memory_size(int bits);


int main(void)
{
        chipset *chip = init_chipset(4);
        delete_chipset(chip);
}


chipset *init_chipset(int bits)
{
        int memory = memory_size(bits);
        chipset *chip = malloc(sizeof(chipset));
        chip->MEMORY = calloc(sizeof(int), memory);
        chip->INSTRUCTIONS = malloc(sizeof(instruction) * memory);
        init_registers(chip);
        chip->EXECUTE = true;
        return chip;
}


void init_registers(chipset *chip)
{
        chip->PC = 0;
        chip->IR = 0;
        chip->R0 = 0;
        chip->R1 = 0;
}


void delete_chipset(chipset *chip)
{
        free(chip->MEMORY);
        free(chip->INSTRUCTIONS);
        free(chip);
}


int memory_size(int bits)
{
        return (int) pow(2, (double) bits);
}
