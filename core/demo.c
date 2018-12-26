#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "chipset.h"

//chipset init_chipset();
int memory_size(double bits);


int main(void)
{
        printf("%d\n", memory_size(4));
        printf("%d\n", memory_size(8));
        printf("%d\n", memory_size(16));
}


//chipset init_chipset()
//{
//        chipset *chip = malloc(sizeof(chip));
//}


int memory_size(double bits)
{
        return (int) pow(2, bits);
}
