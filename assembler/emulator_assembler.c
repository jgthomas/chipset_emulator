#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "emulator_assembler.h"
#include "emulator.h"
#include "conversion.h"
#include "files.h"

#define CODE_LEN 4
#define PADDING 10


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
        {"JMPNZ", JMPNZ},
        {"ASCCHAR", ASCCHAR}
};


void usage(void);
int op_code(char *instruction);
int count_codes(FILE *fp);
char *read_assembly(char *infile);
void write_machine_code(char *outfile, char *buffer);


int main(int argc, char **argv)
{
        if (argc < 2)
        {
                usage();
                exit(EXIT_FAILURE);
        }

        char *program_buffer = read_assembly(argv[1]);

        char *outfile;

        if (argc == 3) {

                outfile = argv[2];
        }
        else
        {
                outfile = "output.o";
        }

        write_machine_code(outfile, program_buffer);

        if (program_buffer)
        {
                free(program_buffer);
        }

        exit(EXIT_SUCCESS);
}


char *read_assembly(char *infile)
{
        FILE *fp = load_file(infile, "r");

        size_t buffer_length = (count_codes(fp) * CODE_LEN) + PADDING;
        char *buffer = calloc(sizeof(char), buffer_length);

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

        return buffer;
}


void write_machine_code(char *outfile, char *buffer)
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


int count_codes(FILE *fp)
{
        char c;
        int count = 0;

        while ((c=getc(fp)) != EOF)
        {
                if (c == '\n' || c == ',')
                {
                        count++;
                }
        }

        rewind(fp);

        return count;
}


void usage(void)
{
        printf("usage: ./emulator_compile input_file [output_file]\n");
}
