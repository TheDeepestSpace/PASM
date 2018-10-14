all: pasm

pasm: obj/main.o obj/pasm_vm.o obj/to_bytecode.o hdr/pasm_vm.h hdr/to_bytecode.h
	gcc obj/main.o obj/pasm_vm.o obj/to_bytecode.o -o out/pasm -lm

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o

obj/pasm_vm.o: src/pasm_vm.c
	gcc -c src/pasm_vm.c -o obj/pasm_vm.o

obj/to_bytecode.o: src/to_bytecode.c
	gcc -c src/to_bytecode.c -o obj/to_bytecode.o
