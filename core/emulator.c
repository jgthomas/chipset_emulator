#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "chipset.h"
#include "instructions.h"
#include "emulator.h"


void init_registers(chipset *chip);
int memory_size(int bits);
void execute_instruction(chipset *chip);
int convert_code(char *hex);


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


int convert_code(char *hex)
{
        return (int) strtol(hex, NULL, 16);
}


void load_program(chipset *chip, char *program)
{
        // make copy to allow freeing of memory and to handle literals
        char *p, *start;
        p = start = strdup(program);

        char *token;
        int i = 0;

        while ( (token = strsep(&p, " ")) != NULL && i < chip->MEMSIZE)
        {
                int op_code = convert_code(token);

                if (op_code < chip->MEMSIZE)
                {
                        chip->MEMORY[i] = op_code;
                        i++;
                }
                else
                {
                        fprintf(stderr, "Memory overflow");
                        exit(EXIT_FAILURE);
                }
        }

        if (start)
        {
                free(start);
        }
}
