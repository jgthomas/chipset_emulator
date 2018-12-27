#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "descriptions.h"
#include "emulator.h"
#include "debugger.h"
#include "chipset.h"


void print_register(int pc, int ir, int r0, int r1);
void print_memory(chipset *chip);
void print_line(void);


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


void print_memory(chipset *chip)
{
        printf("\n   MEMORY");
        print_line();

        int count = 0;

        for (int i = 0; i < chip->MEMSIZE; i++)
        {
                printf("|   %02d   ", chip->MEMORY[i]);
                count++;

                if (count == 4)
                {
                        printf("|");
                        print_line();
                        count = 0;
                }
        }
}


void print_register(int pc, int ir, int r0, int r1)
{
        printf("\n   PC     IR     R0     R1");
        printf("\n-----------------------------");
        printf("\n|      |      |      |      |");
        printf("\n|  %02d  |  %02d  |  %02d  |  %02d  |", pc, ir, r0, r1);
        printf("\n|      |      |      |      |");
        printf("\n-----------------------------");
}


void print_line(void)
{
        printf("\n");
        printf("-------------------------------------");
        printf("\n");
}
