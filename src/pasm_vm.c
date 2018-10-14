#include <math.h>
#include <stdio.h>
#include "../hdr/pasm_vm.h"

void vm_reset(void) {
    vm = (typeof(vm)) { NULL };
}

void decode(
    uint32_t instruction,
    uint16_t *op, uint16_t *arg) {
    *op  = (instruction & 0xff000000) >> 24;
    *arg = (instruction & 0x00ffffff);
}

interpretation_result vm_interpret(uint32_t *bytecode) {
    vm_reset();
    puts("START INTERPRETING");
    vm.ip = bytecode;

    uint16_t opcode, arg;
    for(;;) {
        uint32_t instruction = *vm.ip++;
        decode(instruction, &opcode, &arg);

        switch(opcode) {
            case OP_SET_R0:
                vm.r0 = arg == 0 ? vm.r0 : vm.r1;
                break;
            case OP_SET_R1:
                vm.r1 = arg == 0 ? vm.r0 : vm.r1;
                break;

            case OP_SETI_R0:
                vm.r0 = arg;
                break;
            case OP_SETI_R1:
                vm.r1 = arg;
                break;

            case OP_INC_R0:
                vm.r0++;
                break;
            case OP_INC_R1:
                vm.r1++;
                break;

            case OP_DEC_R0:
                vm.r0--;
                break;
            case OP_DEC_R1:
                vm.r1--;
                break;

            case OP_MUL:
                vm.r0 *= arg == 0 ? vm.r0 : vm.r1;
                break;
            case OP_EXP:
                vm.r0 = (uint32_t) pow(
                    (double) vm.r0,
                    (double) (arg == 0 ? vm.r0 : vm.r1)
                );
                break;

            case OP_MULI:
                vm.r0 *= arg;
                break;
            case OP_EXPI:
                vm.r0 = (uint32_t) pow((double) vm.r0, (double) arg);
                break;

            case OP_XCHG:
                vm.r0 ^= vm.r1;
                vm.r1 ^= vm.r0;
                vm.r0 ^= vm.r1;
                break;

            case OP_CMPI:
                vm.f = vm.r0 == arg;
                break;

            case OP_JMP_IF_F:
                if (vm.f) vm.ip = bytecode + arg;
                break;
            case OP_JMP_IF_NOT_F:
                if (!vm.f) vm.ip = bytecode + arg;
                break;

            case PRINT_R0:
                printf("%d\n", vm.r0);
                break;
            case PRINT_R1:
                printf("%d\n", vm.r1);
                break;

            case HALT:
                puts("DONE INTERPRETING");
                return SUCC;

            default:
                puts("FAIL");
                return FAIL;
        }
    }
}
