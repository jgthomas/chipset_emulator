#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "run.h"
#include "chipset.h"


int main(int argc, char **argv)
{
        if (argc < 2)
        {
                fprintf(stderr, "Insufficient arguments\n");
                exit(EXIT_FAILURE);
        }

        bool debug_on = false;

        if (argc == 3 && (strncmp(argv[2], "d", 1) == 0))
        {
                debug_on = true;
        }

        run(argv[1], EIGHT_BIT, 17, debug_on);

        return EXIT_SUCCESS;
}
