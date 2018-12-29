#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "emulator_assembler.h"
#include "emulator.h"
#include "conversion.h"


#define BUFFER 256


OP_CODE_CONVERT op_code_table[] = {
        {"HALT", HALT},
        {"ADD", ADD},
        {"SUB", SUB},
        {"INC0", INC0},
        {"INC1", INC1},
        {"DEC0", DEC0},
        {"DEC1", DEC1},
        {"SWP", SWP},
        {"PRNT", PRNT},
        {"LD0", LD0},
        {"LD1", LD1},
        {"ST0", ST0},
        {"ST1", ST1},
        {"JMP", JMP},
        {"JMPZ", JMPZ},
        {"JMPNZ", JMPNZ}
};


void usage(void);
int op_code(char *instruction);
void read_assembly(char *infile, char buffer[BUFFER]);
void write_machine_code(char *outfile, char buffer[BUFFER]);


int main(int argc, char **argv)
{
        if (argc < 2)
        {
                usage();
                exit(EXIT_FAILURE);
        }

        char program_buffer[BUFFER] = {0};

        read_assembly(argv[1], program_buffer);

        char *outfile;

        if (argc == 3) {

                outfile = argv[2];
        }
        else
        {
                outfile = "output.o";
        }

        write_machine_code(outfile, program_buffer);

        exit(EXIT_SUCCESS);
}


void read_assembly(char *infile, char buffer[BUFFER])
{
        FILE *fp = fopen(infile, "r");

        if (fp == NULL)
        {
                fprintf(stderr, "Failed to load file '%s'\n", infile);
                exit(EXIT_FAILURE);
        }

        int counter = 0;
        char *line = NULL;
        size_t len = 0;
        char *found;

        char *l, *start;

        while ((getline(&line, &len, fp)) != -1)
        {
                line[strcspn(line, "\r\n")] = 0;

                l = start = strdup(line);

                while ( (found = strsep(&l, ",")) != NULL)
                {
                        int code = op_code(found);
                        snprintf(buffer+counter, 4, "%02x ", code);
                        counter += 3;
                }

                if (start)
                {
                        free(start);
                }
        }

        if (line)
        {
                free(line);
        }

        fclose(fp);
}


void write_machine_code(char *outfile, char buffer[BUFFER])
{
        FILE *fp2 = fopen(outfile, "w");

        if (fp2 == NULL)
        {
                fprintf(stderr, "Failed to open file '%s'\n", outfile);
                exit(EXIT_FAILURE);
        }

        fprintf(fp2, "%s", buffer);
        fclose(fp2);
}


int op_code(char *instruction)
{
        for (int i = 0; i < INSTRUCTION_NUM; i++)
        {
                if (strcmp(instruction, op_code_table[i].code) == 0)
                {
                        return op_code_table[i].op;
                }
        }

        return decimal_string_to_int(instruction);
}


void usage(void)
{
        printf("usage: ./emulator_compile input_file [output_file]\n");
}
