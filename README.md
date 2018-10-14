# PASM
Basic Pseudo-Assembler implementation.

# Running PASM

```sh
pasm code.pasm
```

# Writing PASM

Current version is very picky about input - operations and their arguments should be separated with one and only space, if instruction takes no aguments, an endline character (`\n`) should follow it.

# Behind the CLI

The application plays the role of both source (`.pasm` files) interpreter as well as byte-code interpreter. 

## Architecture of pasmVM

Bytecode interpreter is set up as a virtual machine (wanna be virtual machine actually). 
It's architecture is simple: 
* two 32-bit general-purpose registers (`R0`, `R1`);
* 32-bit instruction pointer register (`IP`);
* single bit flag register (`F`).

## Instruction set of passVM

Consult source code for details.
