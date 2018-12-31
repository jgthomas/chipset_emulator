#ifndef EMULATOR_ASSEMBLER_H
#define EMULATOR_ASSEMBLER_H

#define CODE_LEN 4
#define INSTRUCTION_NUM 17

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
              JMPNZ,
              ASCCHAR,
} OP_CODE;


typedef struct OP_CODE_NUM
{
        char *code;
        OP_CODE op;
} OP_CODE_CONVERT;


OP_CODE_CONVERT op_code_table[] = {
        {"HALT", HALT},
        {"ADD", ADD},
        {"SUB", SUB},
        {"INC0", INC0},
        {"INC1", INC1},
        {"DEC0", DEC0},
        {"DEC1", DEC1},
        {"SWP", SWP},
        {"PRNT", PRNT},
        {"LD0", LD0},
        {"LD1", LD1},
        {"ST0", ST0},
        {"ST1", ST1},
        {"JMP", JMP},
        {"JMPZ", JMPZ},
        {"JMPNZ", JMPNZ},
        {"ASCCHAR", ASCCHAR}
};

#endif
