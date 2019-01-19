#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "chipset.h"
#include "descriptions.h"
#include "emulator.h"


void print_help(bool debug, int instruction_count);
void print_instructions(int instruction_count);
void input(char program[], int size);
void run_program(chipset *chip, char *program);
void run_debug(chipset *chip, char *program);
void clear_screen(void);


int main(int argc, char **argv)
{
        bool debug = false;

        if (argc == 2 && (strncmp(argv[1],"d", 1) == 0))
        {
                debug = true;
        }

        chipset *chip;
        int bits;
        int instruction_count;

        while (true)
        {
                char choice[3];
                printf("select '4' or '8' bit chip\n");
                input(choice, sizeof(choice));
                choice[strcspn(choice, "\n")] = '\0';

                if (strncmp(choice, "4", 1) == 0)
                {
                        bits = FOUR_BIT;
                        instruction_count = 16;
                }
                else if (strncmp(choice, "8", 1) == 0)
                {
                        bits = EIGHT_BIT;
                        instruction_count = 17;
                }
                else
                {
                        fprintf(stderr, "Invalid chip bits\n");
                        continue;
                }

                chip = init_chip(bits, instruction_count);
                break;
        }

        print_help(debug, instruction_count);

        while (true)
        {
                char program[256];
                input(program, sizeof(program));
                program[strcspn(program, "\n")] = '\0';

                if (strncmp(program, "help", 4) == 0)
                {
                        clear_screen();
                        print_help(debug, instruction_count);
                }
                else if (strncmp(program, "clear", 5) == 0)
                {
                        clear_screen();
                }
                else if (strncmp(program, "debug", 5) == 0)
                {
                        debug = true;
                        clear_screen();
                        print_help(debug, instruction_count);
                }
                else if (strncmp(program, "normal", 6) == 0)
                {
                        debug = false;
                        clear_screen();
                        print_help(debug, instruction_count);
                }
                else if (strncmp(program, "quit", 4) == 0)
                {
                        break;
                }
                else
                {
                        if (debug)
                        {
                                run_debug(chip, program);
                        }
                        else
                        {
                                run_program(chip, program);
                        }
                }
        }

        return EXIT_SUCCESS;
}


void run_program(chipset *chip, char *program)
{
        printf("\n %d\n\n", execute(chip, program));
}


void run_debug(chipset *chip, char *program)
{
        printf("\n %d\n\n", debug(chip, program));
}


void input(char program[], int size)
{
        printf(" #> ");
        fgets(program, size, stdin);

        // discard input beyond memory size
        if (!strchr(program, '\n'))
        {
                while (fgetc(stdin) != '\n') {};
        }
}


void clear_screen(void)
{
        const char *clear_screen_unix = "\e[1;1H\e[2J";
        write(STDOUT_FILENO, clear_screen_unix, 12);
}


void print_instructions(int instruction_count)
{
        printf("\ncode   :    instruction\n\n");

        for (int i = 0; i < instruction_count; i++)
        {
                printf(" %02x         %s\n", i, instruction_description[i]);
        }
        printf("\n");
}


void print_help(bool debug, int instruction_count)
{
        if (debug)
        {
                printf("\nDEBUG MODE\n");
        }

        print_instructions(instruction_count);
        printf("Type 'quit' to exit, 'clear' to clear screen,  or 'help' to display all instructions\n\n");
}
