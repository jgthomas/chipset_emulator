#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "chipset.h"
#include "instructions.h"
#include "load.h"


chipset *init_chipset(int bits);
void delete_chipset(chipset *chip);
void init_registers(chipset *chip);
void load_instructions(chipset *chip, int count);
int memory_size(int bits);
void print_memory(chipset *chip);
void load_program(chipset *chip, char *program, int size);
void execute_instruction(chipset *chip);
void execute_program(chipset *chip);


const char *BASE_CODES = "0123456789abcdef";


int main(void)
{
        int bits = 4;
        int instructions = 16;
        char *program = "03 03 03 04 04 04 04";

        char *hex = "ff";
        printf("%d\n", convert_code(hex));

        chipset *chip = init_chipset(bits);
        load_instructions(chip, instructions);

        load(chip, program);

        print_memory(chip);
        execute_program(chip);
        printf("result %d\n", chip->R0);
        delete_chipset(chip);
}


chipset *init_chipset(int bits)
{
        chipset *chip = malloc(sizeof(chipset));

        if (chip == NULL)
        {
                fprintf(stderr, "Failed to allocate memory for chip\n");
                exit(EXIT_FAILURE);
        }

        chip->MEMSIZE = memory_size(bits);

        chip->MEMORY = calloc(sizeof(int), chip->MEMSIZE);

        if (chip->MEMORY == NULL)
        {
                fprintf(stderr, "Failed to allocate memory for chip memory\n");
                exit(EXIT_FAILURE);
        }

        chip->INSTRUCTIONS = malloc(sizeof(instruction) * chip->MEMSIZE);

        if (chip->INSTRUCTIONS == NULL)
        {
                fprintf(stderr, "Failed to allocate memory for chip instructions\n");
                exit(EXIT_FAILURE);
        }

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


void execute_program(chipset *chip)
{
        while (chip->EXECUTE)
        {
                execute_instruction(chip);

                if (chip->PC >= chip->MEMSIZE)
                {
                        fprintf(stderr, "End reached without termination!\n");
                        exit(EXIT_FAILURE);
                }
        }
}


void execute_instruction(chipset *chip)
{
        if (chip->MEMORY[chip->PC] == -1)
        {
                fprintf(stderr, "Program contains invalid instruction code\n");
                exit(EXIT_FAILURE);
        }
        else
        {
                chip->IR = chip->MEMORY[chip->PC];
                chip->INSTRUCTIONS[chip->IR](chip);
        }
}


void print_memory(chipset *chip)
{
        for (int i = 0; i < chip->MEMSIZE; i++)
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
