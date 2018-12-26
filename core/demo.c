#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "chipset.h"

chipset *init_chipset(double bits);
void delete_chipset(chipset *chip);
void init_registers(chipset *chip);
int memory_size(double bits);


int main(void)
{
        printf("%d\n", memory_size(4));
        printf("%d\n", memory_size(8));
        printf("%d\n", memory_size(16));
        chipset *chip = init_chipset(4);
        delete_chipset(chip);
}


chipset *init_chipset(double bits)
{
        int memory = memory_size(bits);
        chipset *chip = malloc(sizeof(chip));
        chip->MEMORY = malloc(sizeof(int) * memory);
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


int memory_size(double bits)
{
        return (int) pow(2, bits);
}
