/**
 * Simulation function
 */

// uncomment this block if wishing to debug
/*
#ifndef DEBUG_SIMULATION
#define DEBUG_SIMULATION
#endif
 */

#ifndef SIMULATION
#include "simulation.hpp"
#endif


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
void simulate(int32_t* mem, const int n_instr){
    // initialise empty Stack
    Stack S;
    
    // set program counter to address 0 of memory
    int PC = 0;
    
    // variables for instructions decode from memory array
    int opcode;
    int operand;
    
    // an opcode of 1 means that the system is halted and the simulation mode is exited
    while (opcode != 1){
        // Fetch instruction at program counter from memory.
        // Decode instruction.
        disassembled_instr d_instr = disassemble(mem[PC]);
        opcode = d_instr.opcode;
        operand = d_instr.operand;
        
#ifdef DEBUG_DISASSEMBLY
        std::cout << "opcode = " << opcode << "\n";
        std::cout << "operand = " << operand << "\n";
#endif
        
        // variable for knowing from which function exceptions are thrown
        std::string str_instr;
        
        // execute instruction
        try{
            if (opcode == 1){
                str_instr = "hlt()";
                hlt();
            } else if (opcode == 10){
                str_instr = "in()";
                in(S, PC);
            } else if (opcode == 11){
                str_instr = "inchar()";
                inchar(S, PC);
            } else if (opcode == 12){
                str_instr = "out()";
                out(S, PC);
            } else if (opcode == 13){
                str_instr = "outchar()";
                outchar(S, PC);
            } else if (opcode == 20){
                str_instr = "add()";
                add(S, PC);
            } else if (opcode == 21){
                str_instr = "sub()";
                sub(S, PC);
            } else if (opcode == 22){
                str_instr = "mul()";
                mul(S, PC);
            } else if (opcode == 23){
                str_instr = "div()";
                div(S, PC);
            } else if (opcode == 24){
                str_instr = "mod()";
                mod(S, PC);
            } else if (opcode == 25){
                str_instr = "neg()";
                neg(S, PC);
            } else if (opcode == 26){
                str_instr = "dup()";
                dup(S, PC);
            } else if (opcode == 30){
                str_instr = "load()";
                load(mem, S, PC);
            } else if (opcode == 31){
                str_instr = "store()";
                store(mem, S, PC);
            } else if (opcode == 32){
                str_instr = "const_c()";
                const_c(operand, S, PC);
            } else if (opcode == 40){
                str_instr = "jmp_c()";
                jmp_c(operand, PC);
            } else if (opcode == 41){
                str_instr = "jeq_c()";
                jeq_c(operand, S, PC);
            } else if (opcode == 42){
                str_instr = "jne_c()";
                jne_c(operand, S, PC);
            } else if (opcode == 43){
                str_instr = "jls_c()";
                jls_c(operand, S, PC);
            } else if (opcode == 44){
                str_instr = "jle_c()";
                jle_c(operand, S, PC);
            } else{
                str_instr = "data";
                ++PC;
            }
            
            if (PC >= n_instr) throw MemOutOfBounds();
            
        } catch(InvalidInput& error){
            std::cerr << "Error: " << str_instr << " failed because of invalid input. The number of instructions should be an integer.\n";
            return;
        } catch(Overflow& error){
            std::cerr << "Error: " << str_instr << " failed because result was greater than maximum integer value that can be stored.\n";
            return;
        } catch(Underflow& error){
            std::cerr << "Error: " << str_instr << " failed because result was smaller than minimum integer value that can be stored.\n";
            return;
        } catch(DivisionByZero& error){
            std::cerr << "Error: " << str_instr << " failed because denominator was zero, so result was undefined.\n";
            return;
        } catch(MemOutOfBounds& message){
            std::cerr << "Message: Program Counter has reached the end of the memory allocated to the input hexadecimal instructions.\n";
            return;
        }
        
#ifdef DEBUG_SIMULATION
        S.print();
        std::cout << "PC = " << PC << "\n";
#endif
        
    }  // end of WHILE loop for running through all instructions in memory array
    
    std::cout << "\n";
    return;
}  // end of void function for simulation
