#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "run.h"
#include "emulator.h"
#include "chipset.h"
#include "files.h"


char *read_in_program(char *filename);
long program_length(FILE *data);


void run(char *filename, int bits, int instruction_count, bool debug_on)
{
        char *program = read_in_program(filename);
        chipset *chip = init_chip(bits, instruction_count);

        if (debug_on)
        {
                printf("\n%d\n", debug(chip, program));
        }
        else
        {
                printf("\n%d\n", execute(chip, program));
        }

        free(program);
        delete_chipset(chip);
}


char *read_in_program(char *filename)
{
        FILE *data = load_file(filename, "r");

        long length = program_length(data);
        char *program = calloc(sizeof(char), length+1);

        if (program == NULL)
        {
                fprintf(stderr, "Cannot allocate memory for program");
                exit(EXIT_FAILURE);
        }

        fread(program, length, 1, data);

        fclose(data);

        return program;
}


long program_length(FILE *data)
{
        fseek(data, 0L, SEEK_END);
        long length = ftell(data);
        rewind(data);
        return length;
}
