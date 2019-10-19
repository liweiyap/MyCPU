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

#include <cmath>
#include <iostream>


/**
 * opcode and operand stored in hexadecimal representation
 */
struct disassembled_instr{
    int opcode;
    int operand;
};  // end of disassembled_instruction struct definition


/**
 * Each hexadecimal instruction is 8 x 4 = 32 bits long (each digit in a hexadecimal being a hex-nibble).
 * The first 2 x 4 = 8 bits are the opcode.
 * The last 6 x 4 = 24 bits are the operand.
 * In this function, we decode/split the instr into the opcode and operand.

 * The instr has been converted to decimal form, so to convert it back to
 * hexadecimal form, we have to divide by powers of 16. We only have to do
 * this twice because the remainder after two rounds of division is already
 * the operand, with the opcode also extracted during division.
 *
 * @param instr instruction that has been cast from its hexadecimal form at input to a decimal integer
 * @return struct containing opcode and operand decoded from instruction
 */
disassembled_instr disassemble(int instr);


/**
 * Disassemble instruction in decimal form into opcode and operand.
 * Print output according to opcode (and, where appropriate, operand).
 */
void disassembly_std_output(int instr);


#endif
