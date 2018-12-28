#ifndef EMULATOR_ASSEMBLER_H
#define EMULATOR_ASSEMBLER_H

#define INSTRUCTION_NUM 16
#define MEM_LEN 16


typedef enum {HALT,
              ADD,
              SUB,
              INC0,
              INC1,
              DEC0,
              DEC1,
              SWP,
              PRNT,
              LD0,
              LD1,
              ST0,
              ST1,
              JMP,
              JMPZ,
              JMPNZ
} OP_CODE;


typedef struct OP_CODE_NUM
{
        char *code;
        OP_CODE op;
} OP_CODE_CONVERT;

#endif
