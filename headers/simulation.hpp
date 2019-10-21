/**
 * Simulation function
 */

#ifndef SIMULATION
#define SIMULATION
#pragma once

#ifndef DISASSEMBLY
#include "disassembly.hpp"
#endif

#ifndef STACK_EXECUTE
#include "stack_execute.hpp"
#endif

#include <string>


/**
 * In simulation mode, we fetch stored instructions from memory array,
 * decode the instructions into opcode and operand,
 * and execute corresponding stack functions.
 *
 * @param mem pointer to an int32_t
 * @param n_instr total number of instructions input and stored in mem array
 * @throws InvalidInput() exception thrown if input is invalid (e.g. not an int in the in() function)
 * @throws Overflow() exception thrown if a value is greater than INT_MAX
 * @throws Underflow() exception thrown if a value is smaller than INT_MIN
 * @throws DivisionByZero() exception thrown if denominator is zero during division
 * @throws MemOutOfBounds() exception thrown if program counter has reached the end of the memory allocated to the input instructions
 */
void simulate(int32_t* mem, const int n_instr);


#endif
