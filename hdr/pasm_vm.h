#include <stdint.h>
#include <stdbool.h>

struct {
    uint32_t *ip;
    uint32_t r0;
    uint32_t r1;
    bool     f;
} vm;

typedef enum {
    OP_SET_R0, OP_SET_R1,
    OP_SETI_R0, OP_SETI_R1,

    OP_INC_R0, OP_INC_R1,
    OP_DEC_R0, OP_DEC_R1,

    OP_MUL, OP_EXP,
    OP_MULI, OP_EXPI,

    OP_XCHG,

    OP_CMP,

    OP_JMP_IF_F,
    OP_JMP_IF_NOT_F,

    PRINT_R0, PRINT_R1,

    HALT
} opcode;

typedef enum {
    SUCC, FAIL
} interpretation_result;

interpretation_result vm_interpret(uint32_t *bytecode);
