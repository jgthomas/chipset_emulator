#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "chipset.h"

chipset *init_chipset(double bits);
void delete_chipset(chipset *chip);
int memory_size(double bits);


int main(void)
{
        printf("%d\n", memory_size(4));
        printf("%d\n", memory_size(8));
        printf("%d\n", memory_size(16));
        chipset *chip = init_chipset(4);
        delete_chipset(chip);
}


chipset *init_chipset(double bits)
{
        chipset *chip = malloc(sizeof(chip));
        chip->MEMORY = malloc(sizeof(int) * (int) bits);
        return chip;
}


void delete_chipset(chipset *chip)
{
        free(chip->MEMORY);
        free(chip);
}


int memory_size(double bits)
{
        return (int) pow(2, bits);
}
