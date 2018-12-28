#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "emulator_assembler.h"
#include "emulator.h"


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


int main(int argc, char **argv)
{
        if (argc < 2)
        {
                usage();
                exit(EXIT_FAILURE);
        }

        FILE *fp = fopen(argv[1], "r");

        if (fp == NULL)
        {
                fprintf(stderr, "Failed to load file '%s'\n", argv[1]);
                exit(EXIT_FAILURE);
        }

        char program_buffer[16] = {0};
        int counter = 0;
        char *line = NULL;
        size_t len = 0;
        char *found;

        while ((getline(&line, &len, fp)) != -1)
        {
                line[strcspn(line, "\r\n")] = 0;

                while ( (found = strsep(&line, ",")) != NULL)
                {
                        int code = op_code(found);
                        snprintf(program_buffer+counter, 4, "%02x ", code);
                        counter += 3;
                }
        }

        char *outfile;

        if (argc == 3) {

                outfile = argv[2];
        }
        else
        {
                outfile = "output.o";
        }

        FILE *fp2 = fopen(outfile, "w");

        if (fp2 == NULL)
        {
                fprintf(stderr, "Failed to open file '%s'\n", outfile);
                exit(EXIT_FAILURE);
        }

        fprintf(fp2, "%s", program_buffer);

        fclose(fp);
        fclose(fp2);

        if (line)
        {
                free(line);
        }

        exit(EXIT_SUCCESS);
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

        return convert_code(instruction);
}


void usage(void)
{
        printf("usage: ./emulator_compile input_file [output_file]\n");
}
