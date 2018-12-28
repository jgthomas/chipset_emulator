#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include "chipset.h"
#include "instructions.h"
#include "emulator.h"
#include "debugger.h"


void init_registers(chipset *chip);
int memory_size(int bits);
void execute_instruction(chipset *chip);
int convert_code(char *hex);
void clear_memory(chipset *chip);
void load_program(chipset *chip, char *program);
void execute_program(chipset *chip);
void load_instructions(chipset *chip, int count);
chipset *init_chipset(int bits);


int execute(chipset *chip, char *program)
{
        init_registers(chip);
        clear_memory(chip);
        load_program(chip, program);
        execute_program(chip);
        return chip->R0;
}


int debug(chipset *chip, char *program)
{
        init_registers(chip);
        clear_memory(chip);
        load_program(chip, program);

        int step = -1;

        print_header(chip, step);
        print_chipset(chip, 0);

        while (chip->EXECUTE)
        {
                printf("\nPress ENTER to continue\n");
                getchar();

                step++;
                print_header(chip, step);
                int prev_pc = chip->PC;
                execute_instruction(chip);
                print_chipset(chip, prev_pc);
        }

        return chip->R0;
}


chipset *init_chip(int bits, int instruction_count)
{
        chipset *chip = init_chipset(bits);
        load_instructions(chip, instruction_count);
        return chip;
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


void clear_memory(chipset *chip)
{
        for (int i = 0; i < chip->MEMSIZE; i++)
        {
                chip->MEMORY[i] = 0;
        }
}


void init_registers(chipset *chip)
{
        chip->PC = 0;
        chip->IR = 0;
        chip->R0 = 0;
        chip->R1 = 0;
        chip->EXECUTE = true;
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
        errno = 0;
        char *endptr;

        long op_code = strtol(hex, &endptr, 16);

        if (errno == ERANGE)
        {
                switch(op_code)
                {
                        case LONG_MIN:
                                fprintf(stderr, "Underflow: op code too high\n");
                                exit(EXIT_FAILURE);
                        case LONG_MAX:
                                fprintf(stderr, "Overflow: op code too low\n");
                                exit(EXIT_FAILURE);

                }
        }
        else if (errno != 0)
        {
                fprintf(stderr, "Unidentified op code error\n");
                exit(EXIT_FAILURE);
        }
        else if (*endptr != '\0' || *hex == '\0')
        {
                fprintf(stderr, "Invalid instruction provided\n");
                exit(EXIT_FAILURE);
        }

        return (int) op_code;
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
