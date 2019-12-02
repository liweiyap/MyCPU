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

#include <iterator>   // begin
#include <ios>        // dec, hex, streamsize


void hlt();
void in(Stack& S, unsigned int& PC);
void inchar(Stack& S, unsigned int& PC);
void out(Stack& S, unsigned int& PC);
void outchar(Stack& S, unsigned int& PC);
void add(Stack& S, unsigned int& PC);
void sub(Stack& S, unsigned int& PC);
void mul(Stack& S, unsigned int& PC);
void div(Stack& S, unsigned int& PC);
void mod(Stack& S, unsigned int& PC);
void neg(Stack& S, unsigned int& PC);
void dup(Stack& S, unsigned int& PC);
void load(int32_t* mem, Stack& S, unsigned int& PC);
void store(int32_t* mem, Stack& S, unsigned int& PC);
void const_c(const int c, Stack& S, unsigned int& PC);
void jmp_c(const int c, unsigned int& PC);
void jeq_c(const int c, Stack& S, unsigned int& PC);
void jne_c(const int c, Stack& S, unsigned int& PC);
void jls_c(const int c, Stack& S, unsigned int& PC);
void jle_c(const int c, Stack& S, unsigned int& PC);


#endif
