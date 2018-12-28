#ifndef CHIPSET_H
#define CHIPSET_H

#include <stdbool.h>

struct chipset;
typedef struct chipset chipset;

typedef void (*instruction)(chipset*);

struct chipset {
        int PC;
        int IR;
        int R0;
        int R1;
        int BITS;
        int MEMSIZE;
        int *MEMORY;
        bool EXECUTE;
        instruction *INSTRUCTIONS;
};

#endif
