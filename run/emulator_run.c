#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emulator.h"
#include "chipset.h"


void run_program(char *filename, int bits, int instruction_count);
void run_debug(char *filename, int bits, int instruction_count);
char *read_in_program(char *filename);
long program_length(FILE *data);


int main(int argc, char **argv) {

        if (argc < 2)
        {
                fprintf(stderr, "Insufficient arguments\n");
                exit(EXIT_FAILURE);
        }

        if (argc == 3 && (strncmp(argv[2],"d", 1) == 0))
        {
                run_debug(argv[1], 4, 16);
        }
        else {
                run_program(argv[1], 4, 16);
        }
}


void run_program(char *filename, int bits, int instruction_count)
{
        char *program = read_in_program(filename);

        chipset *chip = init_chip(bits, instruction_count);
        int result = execute(chip, program);
        printf("%d\n", result);

        free(program);
        delete_chipset(chip);
}


void run_debug(char *filename, int bits, int instruction_count)
{
        char *program = read_in_program(filename);

        chipset *chip = init_chip(bits, instruction_count);
        int result = debug(chip, program);
        printf("%d\n", result);

        free(program);
        delete_chipset(chip);
}


char *read_in_program(char *filename)
{
        FILE *data = fopen(filename, "r");

        if (data == NULL)
        {
                fprintf(stderr, "Cannot locate file '%s'\n", filename);
                exit(EXIT_FAILURE);
        }

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
