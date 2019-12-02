/**
 * Functions required for disassembly mode
 */

#ifndef DISASSEMBLY
#define DISASSEMBLY
#pragma once

// uncomment this block if wishing to debug
/*
#ifndef DEBUG_DISASSEMBLY
#define DEBUG_DISASSEMBLY
#endif
 */

#include <cmath>     // pow
#include <iostream>
#include <ios>       // dec, hex, streamsize


/**
 * opcode and operand stored in hexadecimal representation
 */
struct disassembled_instr{
    int opcode;
    int operand;
};

disassembled_instr disassemble(int instr);

void disassembly_std_output(int instr);

void disassembly_std_output(int32_t* mem, const int n_instr);


#endif
