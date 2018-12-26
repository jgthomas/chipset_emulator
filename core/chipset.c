#include <stdbool.h>
#include "chipset.h"

// function pointer type
typedef void (*instruction)(void);

// chipset definition
struct chipset {
        int PC;
        int IR;
        int R0;
        int R1;
        int *MEMORY;
        bool EXECUTE;
        instruction *INSTRUCTIONS;
};
