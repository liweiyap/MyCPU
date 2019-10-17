// uncomment this block if wishing to debug
/*
#ifndef DEBUG_SIMULATION
#define DEBUG_SIMULATION
#endif
 */

#include "simulation.hpp"

void simulate(int32_t* mem){
    Stack S;
    int PC = 0;
    int opcode;
    int operand;
    
    while (opcode != 1){
        disassembled_instr d_instr = disassemble(mem[PC]);
        opcode = d_instr.opcode;
        operand = d_instr.operand;
#ifdef DEBUG_DISASSEMBLY
        std::cout << "opcode = " << opcode << "\n";
        std::cout << "operand = " << operand << "\n";
#endif
        if (opcode == 1) hlt();
        else if (opcode == 12) out(S, PC);
        else if (opcode == 13) outchar(S, PC);
        else if (opcode == 20) add(S, PC);
        else if (opcode == 21) sub(S, PC);
        else if (opcode == 26) dup(S, PC);
        else if (opcode == 30) load(mem, S, PC);
        else if (opcode == 31) store(mem, S, PC);
        else if (opcode == 32) const_c(operand, S, PC);
        else if (opcode == 40) jmp_c(operand, PC);
        else if (opcode == 41) jeq_c(operand, S, PC);
#ifdef DEBUG_SIMULATION
        S.print();
        std::cout << "PC = " << PC << "\n";
#endif
    }
    
    std::cout << "\n";
}
