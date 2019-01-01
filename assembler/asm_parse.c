#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "asm_parse.h"


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
