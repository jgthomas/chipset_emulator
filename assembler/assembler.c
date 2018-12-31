#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "assembler.h"
#include "emulator.h"
#include "conversion.h"
#include "files.h"


void usage(void);
int op_code(char *instruction);
int count_codes(FILE *fp);
bool is_label(char *str);
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

        char *outfile = "output.o";

        if (argc == 3) {

                outfile = argv[2];
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

        size_t buffer_length = count_codes(fp) * CODE_LEN;
        char *buffer = calloc(sizeof(char), buffer_length);
        assert(buffer != NULL);

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
        FILE *f_stream_out = load_file(outfile, "w");
        fprintf(f_stream_out, "%s", buffer);
        fclose(f_stream_out);
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


bool is_label(char *str)
{
        if (str[strlen(str)-1] == ':')
        {
                return true;
        }

        return false;
}


void usage(void)
{
        printf("usage: ./emulator_compile input_file [output_file]\n");
}
