#ifndef STACK_EXECUTE
#define STACK_EXECUTE

#pragma once

#include "stack.hpp"

void hlt();

void out(Stack& S, int& PC);

void outchar(Stack& S, int& PC);

void add(Stack& S, int& PC);

void sub(Stack& S, int& PC);

void dup(Stack& S, int& PC);

void load(int32_t* mem, Stack& S, int& PC);

void store(int32_t* mem, Stack& S, int& PC);

void const_c(const int c, Stack& S, int& PC);

void jmp_c(const int c, int& PC);

void jeq_c(const int c, Stack& S, int& PC);

#endif
