#ifndef DISASSEMBLY
#define DISASSEMBLY

#pragma once

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
