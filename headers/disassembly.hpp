#ifndef DISASSEMBLY
#define DISASSEMBLY
#pragma once

// uncomment this block if wishing to debug
/*
#ifndef DEBUG_DISASSEMBLY
#define DEBUG_DISASSEMBLY
#endif
 */

#include <cmath>
#include <iostream>

// mnemonic and operand stored in hexadecimal representation
struct disassembled_instr{
    int opcode;
    int operand;
};

disassembled_instr disassemble(int instr);

void disassembly_std_output(int instr);

#endif
