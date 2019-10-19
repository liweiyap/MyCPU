/**
 * List of possible functions that can be executed on the stack
 * according to decoded instructions during simulation.
*/

#ifndef STACK_EXECUTE
#define STACK_EXECUTE
#pragma once

#ifndef STACK_H
#include "stack.hpp"
#endif

#ifndef EXCEPTIONS
#include "exceptions.hpp"
#endif

#ifndef STD_INPUT_PARSER
#include "std_input_parser.hpp"
#endif


/**
 * Halt the system (exit the simulator).
 */
void hlt();


/**
 * Read a decimal integer value v from standard input, and push v onto operand stack.
 * Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 */
void in(Stack& S, int& PC);


/**
 * Read a character value v from standard input, and push v onto operand stack.
 * Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 */
void inchar(Stack& S, int& PC);


/**
 * Pop the top value v from operand stack, and write v to standard output as decimal integer.
 * Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 */
void out(Stack& S, int& PC);


/**
 * Pop the top value v from operand stack, and write v to standard output as character.
 * Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 */
void outchar(Stack& S, int& PC);


/**
 * Pop value r from operand stack. Pop value l from operand stack.
 * Push value l+r onto operand stack. Then, increment program counter.
 * @throws Overflow() exception thrown if result of addition is greater than INT_MAX
 * @throws Underflow() exception thrown if result of addition is smaller than INT_MIN
 *
 * @param S operand stack
 * @param PC program counter
 */
void add(Stack& S, int& PC);


/**
 * Pop value r from operand stack. Pop value l from operand stack.
 * Push value l-r onto operand stack. Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of subtraction is greater than INT_MAX
 * @throws Underflow() exception thrown if result of subtraction is smaller than INT_MIN
 */
void sub(Stack& S, int& PC);


/**
 * Pop value r from operand stack. Pop value l from operand stack.
 * Push value l*r onto operand stack. Then, increment program counter.
 * @throws Overflow() exception thrown if result of multiplication is greater than INT_MAX
 * @throws Underflow() exception thrown if result of multiplication is smaller than INT_MIN
 *
 * @param S operand stack
 * @param PC program counter
 */
void mul(Stack& S, int& PC);


/**
 * Pop value r from operand stack. Pop value l from operand stack.
 * Push value l/r (integer division) onto operand stack. Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of division is greater than INT_MAX
 * @throws DivisionByZero() exception thrown if denominator of division is equal to zero
 */
void div(Stack& S, int& PC);


/**
 * Pop value r from operand stack. Pop value l from operand stack.
 * Push value l%r onto operand stack. Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of modulo is greater than INT_MAX
 * @throws DivisionByZero() exception thrown if denominator of division is equal to zero
 */
void mod(Stack& S, int& PC);


/**
 * Pop value r from operand stack. Push value -r onto operand stack.
 * Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of negation is greater than INT_MAX
 */
void neg(Stack& S, int& PC);


/**
 * Pop value r from operand stack. Push value r onto operand stack twice.
 * Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 */
void dup(Stack& S, int& PC);


/**
 * Pop value m from operand stack.
 * Push int32_t value r stored at memory location m onto operand stack.
 * Then, increment program counter.
 *
 * @param mem pointer to memory array of 32-bit signed integer values
 * @param S operand stack
 * @param PC program counter
 */
void load(int32_t* mem, Stack& S, int& PC);


/**
 * Pop value m from operand stack. Pop value v from operand stack.
 * Store v at memory location m as int32_t.
 * Then, increment program counter.
 *
 * @param mem pointer to memory array of 32-bit signed integer values
 * @param S operand stack
 * @param PC program counter
 */
void store(int32_t* mem, Stack& S, int& PC);


/**
 * Push value c onto operand stack. Then, increment program counter.
 *
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void const_c(const int c, Stack& S, int& PC);


/**
 * Set program counter to value c.
 *
 * @param c signed integer operand decoded from input instruction
 * @param PC program counter
 */
void jmp_c(const int c, int& PC);


/**
 * Jump if equal:
 * Pop value r from operand stack. Pop value l from operand stack.
 * If l == r, then set program counter to value c. Else, increment program counter.
 *
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void jeq_c(const int c, Stack& S, int& PC);


/**
 * Jump if not equal:
 * Pop value r from operand stack. Pop value l from operand stack.
 * If l != r, then set program counter to value c. Else, increment program counter.
 *
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void jne_c(const int c, Stack& S, int& PC);


/**
 * Jump if less:
 * Pop value r from operand stack. Pop value l from operand stack.
 * If l < r, then set program counter to value c. Else, increment program counter.
 *
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void jls_c(const int c, Stack& S, int& PC);


/**
 * Jump if less or equal:
 * Pop value r from operand stack. Pop value l from operand stack.
 * If l <= r, then set program counter to value c. Else, increment program counter.
 *
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void jle_c(const int c, Stack& S, int& PC);


#endif
