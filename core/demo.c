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
int map_to_instruction_code(char c);
char map_to_input_code(int n);
void load_program(chipset *chip, char *program, int size, int memory);


const char *BASE_CODES = "0123456789abcdef";


int main(void)
{
        int bits = 4;
        int instructions = 16;
        char *program = "3334444";
        int prog_len = 7;

        chipset *chip = init_chipset(bits);
        load_instructions(chip, instructions);
        load_program(chip, program, prog_len, memory_size(bits));
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


void load_program(chipset *chip, char *program, int size, int memory)
{
        for (int i = 0; i < size && i < memory; i++)
        {
                chip->MEMORY[i] = map_to_instruction_code(*(program+i));
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

/* translate between input and instruction codes */

int map_to_instruction_code(char c)
{
        if (c >= '0' && c <= '9')
        {
                return (int)c - '0';
        }
        else if (c >= 'a' && c <= 'f')
        {
                return (int)(c - 'a') + 10;
        }
        else
        {
                return -1;
        }
}


char map_to_input_code(int n)
{
        if (n >= 0 && n <= 9)
        {
                return (char)n + '0';
        }
        else if (n >= 10 && n <= 15)
        {
                return (char)(n + 'a') - 10;
        }
        else
        {
                return '0';
        }
}
