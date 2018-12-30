#include <stdio.h>
#include <stdlib.h>


FILE *load_file(char *file_stream_name, char *mode)
{
        FILE *f_stream = fopen(file_stream_name, mode);

        if (f_stream == NULL)
        {
                fprintf(stderr, "Failed to access file '%s'\n", file_stream_name);
                exit(EXIT_FAILURE);
        }

        return f_stream;
}
