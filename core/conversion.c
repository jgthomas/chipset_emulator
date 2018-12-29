#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "conversion.h"


static int convert_to_number(char *string, int base);


int hex_string_to_int(char *string)
{
        return convert_to_number(string, HEX);
}


int decimal_string_to_int(char *string)
{
        return convert_to_number(string, DECIMAL);
}


static int convert_to_number(char *string, int base)
{
        errno = 0;
        char *endptr;

        int op_code = strtol(string, &endptr, base);

        if (errno == ERANGE)
        {
                switch(op_code)
                {
                        case INT_MIN:
                                fprintf(stderr, "Underflow: op code too high\n");
                                exit(EXIT_FAILURE);
                        case INT_MAX:
                                fprintf(stderr, "Overflow: op code too low\n");
                                exit(EXIT_FAILURE);
                }
        }
        else if (errno != 0)
        {
                fprintf(stderr, "Unidentified op code error\n");
                exit(EXIT_FAILURE);
        }
        else if (*endptr != '\0' && *endptr != '\n')
        {
                fprintf(stderr, "Invalid instruction provided\n");
                exit(EXIT_FAILURE);
        }

        return op_code;
}
