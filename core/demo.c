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
void print_memory(chipset *chip, int memory);


const char *BASE_CODES = "0123456789abcdef";


int main(void)
{
        int bits = 4;
        int instructions = 16;

        chipset *chip = init_chipset(bits);
        load_instructions(chip, instructions);
        chip->R0 = 2;
        chip->R1 = 2;
        chip->INSTRUCTIONS[1](chip);
        printf("%d\n", chip->R0);
        print_memory(chip, memory_size(bits));
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


void print_memory(chipset *chip, int memory)
{
        for (int i = 0; i < memory; i++)
        {
                printf("%d ", chip->MEMORY[i]);
        }
        printf("\n");
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
