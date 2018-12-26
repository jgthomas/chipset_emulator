#ifndef CHIPSET_H
#define CHIPSET_H

#include <stdbool.h>

typedef void (*instruction)(void);

typedef struct chipset {
        int PC;
        int IR;
        int R0;
        int R1;
        int *MEMORY;
        bool EXECUTE;
        instruction *INSTRUCTIONS;
} chipset;

#endif
