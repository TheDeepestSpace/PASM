#include <stdlib.h>
#include <string.h>

#include "../hdr/to_bytecode.h"

uint32_t* to_bytecode(FILE* fp, uint32_t *bytecode) {
    char ch;
    char op[15];
    char arg[15];
    int idx = 0;
    uint32_t bytecode_idx = 0;
    memset(op, 0, 15 * (sizeof op[0]) );
    while ((ch = fgetc(fp)) != EOF) {
        //printf("%d\n", ch);
        if (ch == ' ') {
            idx = 0;
            memset(arg, 0, 15 * (sizeof arg[0]) );
            while ((ch = fgetc(fp)) != EOF) {
                if (ch == '\x0a')
                    break;
                arg[idx++] = ch;
            }

            //puts(op);

            //printf("%d", atoi(arg));
            //printf("%d", 0x0000000 | atoi(arg) & 0x00ffffff);

            if (!strcmp(op, "SET_R0")) {
                bytecode[bytecode_idx] = 0x00000000;
                if (!strcmp(arg, "R0"))
                    bytecode[bytecode_idx] |= 0x00000000;
                else if (!strcmp(arg, "R1"))
                    bytecode[bytecode_idx] |= 0x00000001;
                else puts("IDIOT");
            } else if (!strcmp(op, "SET_R1")) {
                bytecode[bytecode_idx] = 0x01000000;
                if (!strcmp(arg, "R0"))
                    bytecode[bytecode_idx] |= 0x00000000;
                else if (!strcmp(arg, "R1"))
                    bytecode[bytecode_idx] |= 0x00000001;
                else puts("IDIOT");
            } else if (!strcmp(op, "SETI_R0")) {
                bytecode[bytecode_idx] = 0x02000000;
                bytecode[bytecode_idx] |= 0x00ffffff & atoi(arg);
            } else if (!strcmp(op, "SETI_R1")) {
                bytecode[bytecode_idx] = 0x03000000;
                bytecode[bytecode_idx] |= 0x00ffffff & atoi(arg);
            }else if (!strcmp(op, "MUL")) {
                bytecode[bytecode_idx] = 0x08000000;
                if (!strcmp(arg, "R0"))
                    bytecode[bytecode_idx] |= 0x00000000;
                else if (!strcmp(arg, "R1"))
                    bytecode[bytecode_idx] |= 0x00000001;
                else puts("IDIOT");
            } else if (!strcmp(op, "EXP")) {
                bytecode[bytecode_idx] = 0x09000000;
                if (!strcmp(arg, "R0"))
                    bytecode[bytecode_idx] |= 0x00000000;
                else if (!strcmp(arg, "R1"))
                    bytecode[bytecode_idx] |= 0x00000001;
                else puts("IDIOT");
            } else if (!strcmp(op, "MULI")) {
                bytecode[bytecode_idx] = 0x0a000000;
                bytecode[bytecode_idx] |= 0x00ffffff & atoi(arg);
            } else if (!strcmp(op, "EXPI")) {
                bytecode[bytecode_idx] = 0x0b000000;
                bytecode[bytecode_idx] |= 0x00ffffff & atoi(arg);
            } else if (!strcmp(op, "CMP")) {
                bytecode[bytecode_idx] = 0x0d000000;
                bytecode[bytecode_idx] |= 0x00ffffff & atoi(arg);
            } else if (!strcmp(op, "JMP_IF_F")) {
                bytecode[bytecode_idx] = 0x0e000000;
                bytecode[bytecode_idx] |= 0x00ffffff & atoi(arg);
            } else if (!strcmp(op, "JMP_IF_NOT_F")) {
                bytecode[bytecode_idx] = 0x0f000000;
                bytecode[bytecode_idx] |= 0x00ffffff & atoi(arg);
            } else puts("IDIOT");
            //printf("%x\n", bytecode[bytecode_idx]);
            bytecode_idx++;
            memset(op, 0, 15 * (sizeof op[0]) );
            idx = 0;
        } else if (ch == '\x0a') {
            if (!strcmp(op, "INC_R0"))
                bytecode[bytecode_idx] = 0x04000000;
            else if (!strcmp(op, "INC_R1"))
                bytecode[bytecode_idx] = 0x05000000;
            else if (!strcmp(op, "DEC_R0"))
                bytecode[bytecode_idx] = 0x06000000;
            else if (!strcmp(op, "DEC_R1"))
                bytecode[bytecode_idx] = 0x07000000;
            else if (!strcmp(op, "XCHG"))
                bytecode[bytecode_idx] = 0x0c000000;
            else if (!strcmp(op, "PRINT_R0"))
                bytecode[bytecode_idx] = 0x10000000;
            else if (!strcmp(op, "PRINT_R1"))
                bytecode[bytecode_idx] = 0x11000000;
            else if (!strcmp(op, "HALT"))
                bytecode[bytecode_idx] = 0x12000000;
            else puts("IDIOT");

            bytecode_idx++;
            memset(op, 0, 15 * (sizeof op[0]) );
            idx = 0;
        } else op[idx++] = ch;
    }
    return bytecode;
}
