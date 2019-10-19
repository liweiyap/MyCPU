#ifndef SIMULATION
#define SIMULATION
#pragma once

#ifndef DISASSEMBLY
#include "disassembly.hpp"
#endif

#ifndef STACK_EXECUTE
#include "stack_execute.hpp"
#endif

void simulate(int32_t* mem, const int n_instr);

#endif
