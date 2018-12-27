#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chipset.h"


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
                        chip->MEMORY[i] = convert_code(token);
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
