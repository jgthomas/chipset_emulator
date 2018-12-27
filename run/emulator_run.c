#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emulator.h"


void run_program(char *filename);
void run_debug(char *filename);
char *read_in_program(char *filename);


int main(int argc, char **argv) {

        if (argc < 2)
        {
                fprintf(stderr, "Insufficient arguments\n");
                exit(EXIT_FAILURE);
        }

        if (argc == 3 && (strncmp(argv[2],"d", 1) == 0))
        {
                run_debug(argv[1]);
        }
        else {
                run_program(argv[1]);
        }
}


void run_program(char *filename)
{
        char *prog_to_run = read_in_program(filename);

        init_chip(BASE_CODES);

        int result = emulate(prog_to_run, strlen(prog_to_run));
        printf("%d\n", result);

        free(prog_to_run);
}


void run_debug(char *filename)
{
        char *prog_to_run = read_in_program(filename);

        init_chip(BASE_CODES);

        int result = debug(prog_to_run, strlen(prog_to_run));
        printf("%d\n", result);

        free(prog_to_run);
}


char *read_in_program(char *filename)
{
        FILE *data = fopen(filename, "r");

        if (data == NULL)
        {
                fprintf(stderr, "Cannot locate file '%s'\n", filename);
                exit(EXIT_FAILURE);
        }

        fseek(data, 0L, SEEK_END);
        long progLen = ftell(data);
        rewind(data);
        char *prog_to_run = calloc(sizeof(char), progLen+1);
        fread(prog_to_run, progLen, 1, data);

        fclose(data);

        return prog_to_run;
}
