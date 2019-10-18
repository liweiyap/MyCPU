#ifndef STACK_EXECUTE
#define STACK_EXECUTE
#pragma once

#ifndef STACK_H
#include "stack.hpp"
#endif

#ifndef EXCEPTIONS
#include "exceptions.hpp"
#endif

void hlt();

void in(Stack& S, int& PC);

void inchar(Stack& S, int& PC);

void out(Stack& S, int& PC);

void outchar(Stack& S, int& PC);

void add(Stack& S, int& PC);

void sub(Stack& S, int& PC);

void mul(Stack& S, int& PC);

void div(Stack& S, int& PC);

void mod(Stack& S, int& PC);

void neg(Stack& S, int& PC);

void dup(Stack& S, int& PC);

void load(int32_t* mem, Stack& S, int& PC);

void store(int32_t* mem, Stack& S, int& PC);

void const_c(const int c, Stack& S, int& PC);

void jmp_c(const int c, int& PC);

void jeq_c(const int c, Stack& S, int& PC);

void jne_c(const int c, Stack& S, int& PC);

void jls_c(const int c, Stack& S, int& PC);

void jle_c(const int c, Stack& S, int& PC);

#endif
