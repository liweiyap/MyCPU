#include "headers/exceptions.hpp"
#include "headers/std_input_parser.hpp"
#include "headers/disassembly.hpp"
#include "headers/stack.hpp"

// uncomment this block if wishing to debug
/*
#ifndef DEBUG_MAIN
#define DEBUG_MAIN
#endif
 */

// TODO: fetch, decode, execute for simulator
// TODO: tests for disassembly input etc, stack, simulation input etc
// TODO: exceptions for overflow, underflow, division by zero, memory out of bounds
// TODO: try uniqStack
// TODO: try !(std::cin >> n_instr) for n_instr being int

void hlt(){
    return;
}

void out(Stack& S, int& PC){
    int v = S.peek();
    S.pop();
    std::cout << std::dec << v;
    ++PC;
}

void outchar(Stack& S, int& PC){
    char v = static_cast<char>(S.peek());
    S.pop();
    std::cout << v;
    ++PC;
}

void add(Stack& S, int& PC){
    int r = S.peek();
    S.pop();
    int l = S.peek();
    S.pop();
    S.push(l+r);
    ++PC;
}

void sub(Stack& S, int& PC){
    int r = S.peek();
    S.pop();
    int l = S.peek();
    S.pop();
    S.push(l-r);
    ++PC;
}

void dup(Stack& S, int& PC){
    int r = S.peek();
    S.push(r);
    ++PC;
}

void load(int32_t* mem, Stack& S, int& PC){
    int m = S.peek();
    S.pop();
    int32_t r = mem[m];
    S.push(r);
    ++PC;
}

void store(int32_t* mem, Stack& S, int& PC){
    int m = S.peek();
    S.pop();
    int32_t v = static_cast<int32_t>(S.peek());
    S.pop();
    mem[m] = v;
    ++PC;
}

void const_c(const int c, Stack& S, int& PC){
    S.push(c);
    ++PC;
}

void jmp_c(const int c, int& PC){
    PC = c;
}

void jeq_c(const int c, Stack& S, int& PC){
    int r = S.peek();
    S.pop();
    int l = S.peek();
    S.pop();
    if (l == r) PC = c;
    else ++PC;
}

int main(){
    // input first command as either "disassemble" or "simulate"
    char cmd[12];
    std::cin >> cmd;
    
    // throw exception if first command is neither "disassemble" nor "simulate"
    try{
        if (strcmp(cmd, "disassemble") && strcmp(cmd, "simulate")){
            throw InvalidInput();
        }
    } catch(InvalidInput& err) {
        std::cerr << "Invalid input: please try again. The first command must be either disassemble or simulate.\n";
        return 1;
    }
    
#ifdef DEBUG_MAIN
    if (strcmp(cmd, "disassemble") == 0) std::cout << "disassemble cmd received\n";
    if (strcmp(cmd, "simulate") == 0) std::cout << "simulate cmd received\n";
#endif
    
    // input number of instructions as positive integer
    char tmp_n_instr[11];
    std::cin >> tmp_n_instr;
    int n_instr;
    try{
        // check that there are no inputs like '10a', 'a10', '10.0', or '-10'
        n_instr = ConvertCharToPositiveInt(tmp_n_instr);
    } catch(InvalidInput& err) {
        std::cerr << "Invalid input: please try again. The number of instructions should be a positive integer.\n";
        return 1;
    }
    
#ifdef DEBUG_MAIN
    std::cout << n_instr << "\n";
#endif
    
    if (strcmp(cmd, "disassemble") == 0){
        // input all instructions
        for (int idx_instr = 1; idx_instr <= n_instr; ++idx_instr){
            /* receive instruction as char so that it is easier to filter out large
               hexadecimals that are larger than 0x7fffffff or invalid hexadecimals
               that contain characters like 'g'
             */
            char tmp_instr[256];
            std::cin >> std::hex >> tmp_instr;
            
            /* if we can detect early on that instruction is invalid, then just terminate
               right away and move on to the next instruction
             */
            if (!IsValidHexadecimal(tmp_instr)){
                std::cout << "data " << tmp_instr << "\n";
                continue;
            }
            
            // convert char (in hexidecimal form) to long to int (in decimal form)
            int instr = static_cast<int>(strtol(tmp_instr, NULL, 16));
            
            // disassemble instruction in decimal form into opcode and operand
            // print output according to opcode (and, where appropriate, operand)
            disassembly_std_output(instr);
        }
        
        std::cout << "end\n";
    }
    
    if (strcmp(cmd, "simulate") == 0){
        // dynamic memory allocation because we know n_instr only at run time rather than compile time
        int32_t* mem = new int32_t[n_instr];
        
        for (int idx_instr = 1; idx_instr <= n_instr; ++idx_instr){
            int32_t instr;
            std::cin >> std::hex >> instr;
            
            try{
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidInput();
                }
            } catch(InvalidInput& err) {
                std::cerr << "Invalid instruction: please input hexadecimal between 0x00000000 and 0x7fffffff.\n";
                return 1;
            }
            
            mem[idx_instr-1] = instr;
        }
        
#ifdef DEBUG_MAIN
        for (int PC = 0; PC < n_instr; ++PC)
            std::cout << std::hex << mem[PC] << "\n";
#endif
        
        Stack S;
        int PC = 0;
        int opcode;
        int operand;
        
        while (opcode != 1){
            disassembled_instr d_instr = disassemble(mem[PC]);
            opcode = d_instr.opcode;
            operand = d_instr.operand;
#ifdef DEBUG_MAIN
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
//            S.print();
//            std::cout << "PC = " << PC << "\n";
        }
        
        std::cout << "\n";
        
#ifdef DEBUG_MAIN
        Stack s1(6);
        s1.push(1); s1.push(2); s1.push(3);
        s1.print();
        Stack s2;
        s2.push(5); s2.push(4);
        s2 = s1;
        s1.pop(); s1.print();
        s2.pop(); s2.print();
#endif
        
//        std::shared_ptr<Stack> s1 = std::make_shared<Stack>(6);
//        s1->push(1); s1->push(2); s1->push(3);
//        s1->print();
//        std::shared_ptr<Stack> s2 = std::make_shared<Stack>();
//        s2 = s1;
//        s1->pop(); s1->print();
//        s2->pop(); s2->print();
        
        delete[] mem;
    }
    
    return 0;
}
