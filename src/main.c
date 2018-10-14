#include "../hdr/to_bytecode.h"
#include "../hdr/pasm_vm.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        puts("NO");
        return -1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        puts("BAD FILE");
        return -1;
    } else {
        uint32_t bytecode[500];
        to_bytecode(fp, bytecode);
        return vm_interpret(bytecode);
    }
}
