#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "descriptions.h"
#include "emulator.h"
#include "debugger.h"
#include "chipset.h"


static void print_register(int pc, int ir, int r0, int r1);
static void print_memory(chipset *chip);
static void print_four_bit_line(void);
static void print_line(int repeats);


void print_header(chipset *chip, int step)
{
        if (step == -1)
        {
                printf("\n\nLOADED PROGRAM\n");
        }
        else
        {
                printf("\n\nSTEP: %d\nINSTRUCTION: %d (%s)\n",
                                step,
                                chip->MEMORY[chip->PC],
                                instruction_description[chip->MEMORY[chip->PC]]);
        }
}


void print_chipset(chipset *chip, int prev_pc)
{
        print_register(prev_pc, chip->IR, chip->R0, chip->R1);
        print_memory(chip);
}


static void print_memory(chipset *chip)
{
        printf("\n   MEMORY");
        print_line(chip->BITS / FOUR_BIT);

        int count = 0;

        for (int i = 0; i < chip->MEMSIZE; i++)
        {
                printf("|   %02d   ", chip->MEMORY[i]);
                count++;

                if (count == chip->BITS)
                {
                        printf("|");
                        print_line(chip->BITS / FOUR_BIT);
                        count = 0;
                }
        }
}


static void print_register(int pc, int ir, int r0, int r1)
{
        printf("\n   PC     IR     R0     R1");
        printf("\n-----------------------------");
        printf("\n|      |      |      |      |");
        printf("\n|  %02d  |  %02d  |  %02d  |  %02d  |", pc, ir, r0, r1);
        printf("\n|      |      |      |      |");
        printf("\n-----------------------------");
}


static void print_line(int repeats)
{
        printf("\n");

        for (int i = 0; i < repeats; i++)
        {
                print_four_bit_line();
        }

        printf("\n");
}


static void print_four_bit_line(void)
{
        printf("-------------------------------------");
}
