#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "chipset.h"
#include "instructions.h"


chipset *init_chipset(int bits);
void delete_chipset(chipset *chip);
void init_registers(chipset *chip);
void load_instructions(chipset *chip, int count);
int memory_size(int bits);


const char *BASE_CODES = "0123456789abcdef";

static void (*INSTRUCTIONS[])() = {halt,
                                   add,
                                   subtract,
                                   increment_r0,
                                   increment_r1,
                                   decrement_r0,
                                   decrement_r1,
                                   swap,
                                   print,
                                   load_into_r0,
                                   load_into_r1,
                                   store_r0_in_address,
                                   store_r1_in_address,
                                   jump_to_address,
                                   jump_if_r0_zero,
                                   jump_if_r0_not_zero};

int main(void)
{
        chipset *chip = init_chipset(4);
        load_instructions(chip, 16);
        chip->R0 = 2;
        chip->R1 = 2;
        chip->INSTRUCTIONS[1](chip);
        printf("%d\n", chip->R0);
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


void load_instructions(chipset *chip, int count)
{
        for (int i = 0; i < count; i++)
        {
                chip->INSTRUCTIONS[i] = INSTRUCTIONS[i];
        }
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
