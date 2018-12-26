#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "chipset.h"

chipset *init_chipset(double bits);
void free_chipset(chipset *chip);
int memory_size(double bits);


int main(void)
{
        printf("%d\n", memory_size(4));
        printf("%d\n", memory_size(8));
        printf("%d\n", memory_size(16));
        init_chipset(4);
}


chipset *init_chipset(double bits)
{
        chipset *chip = malloc(sizeof(chip));
        chip->MEMORY = malloc(sizeof(int*) * (int) bits);
        return chip;
}


void free_chipset(chipset *chip)
{
        free(chip);
}


int memory_size(double bits)
{
        return (int) pow(2, bits);
}
