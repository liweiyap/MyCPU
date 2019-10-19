// uncomment this block if wishing to debug
/*
#ifndef DEBUG_SIMULATION
#define DEBUG_SIMULATION
#endif
 */

#ifndef SIMULATION
#include "simulation.hpp"
#endif

void simulate(int32_t* mem, const int n_instr){
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
        std::string str_instr;
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
    }
    
    std::cout << "\n";
    return;
}
