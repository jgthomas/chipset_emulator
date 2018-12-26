#include <stdio.h>
#include <stdbool.h>
#include "chipset.h"


/* one-byte instructions */
void halt(chipset *chip)
{
        chip->EXECUTE = false;
}

void add(chipset *chip)
{
        chip->R0 += chip->R1;
        chip->PC += 1;
}

void subtract(chipset *chip)
{
        chip->R0 -= chip->R1;
        chip->PC += 1;
}

void increment_r0(chipset *chip)
{
        chip->R0 += 1;
        chip->PC += 1;
}

void increment_r1(chipset *chip)
{
        chip->R1 += 1;
        chip->PC += 1;
}

void decrement_r0(chipset *chip)
{
        chip->R0 -= 1;
        chip->PC += 1;
}

void decrement_r1(chipset *chip)
{
        chip->R1 -= 1;
        chip->PC += 1;
}

void swap(chipset *chip)
{
        int temp = chip->R0;
        chip->R0 = chip->R1;
        chip->R1 = temp;
        chip->PC += 1;
}

/* two-byte instructions */
void print(chipset *chip)
{
        printf("%d\n", chip->MEMORY[chip->PC+1]);
        chip->PC += 2;
}

void load_into_r0(chipset *chip)
{
        chip->R0 = chip->MEMORY[chip->MEMORY[chip->PC+1]];
        chip->PC += 2;
}

void load_into_r1(chipset *chip)
{
        chip->R1 = chip->MEMORY[chip->MEMORY[chip->PC+1]];
        chip->PC += 2;
}

void store_r0_in_address(chipset *chip)
{
        chip->MEMORY[chip->MEMORY[chip->PC+1]] = chip->R0;
        chip->PC += 2;
}

void store_r1_in_address(chipset *chip)
{
        chip->MEMORY[chip->MEMORY[chip->PC+1]] = chip->R1;
        chip->PC += 2;
}

void jump_to_address(chipset *chip)
{
        chip->PC = chip->MEMORY[chip->PC+1];
}

void jump_if_r0_zero(chipset *chip)
{
        if (chip->R0 == 0)
        {
                chip->PC = chip->MEMORY[chip->PC+1];
        }
        else
        {
                chip->PC += 2;
        }
}

void jump_if_r0_not_zero(chipset *chip)
{
        if (chip->R0 != 0)
        {
                chip->PC = chip->MEMORY[chip->PC+1];
        }
        else
        {
                chip->PC += 2;
        }
}
