/**
 * First, input either "disassemble" or "simulate".
 * Next, input number of instructions.
 * Lastly, input all instructions.
 */

// uncomment this block if wishing to debug
/*
#ifndef DEBUG_MAIN
#define DEBUG_MAIN
#endif
 */

#ifndef EXCEPTIONS
#include "headers/exceptions.hpp"
#endif

#ifndef STD_INPUT_PARSER
#include "headers/std_input_parser.hpp"
#endif

#ifndef DISASSEMBLY
#include "headers/disassembly.hpp"
#endif

#ifndef SIMULATION
#include "headers/simulation.hpp"
#endif

// TODO: tests for disassembly input etc, stack, simulation input etc
// TODO: try uniqStack
// TODO: rewrite inputs for disassembly mode
// TODO: cout << "Input mode", including for in and inchar
// TODO: edit README

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
    } catch(Overflow& err) {
        std::cerr << "Invalid input: please try again. The number of instructions should be an integer between 0 and (2^31)-1 inclusive.\n";
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
        }  // end FOR loop for inputting instr
        
        std::cout << "end\n";
    }  // end if statement for entering disassembly mode
    
    if (strcmp(cmd, "simulate") == 0 && n_instr != 0){
        // dynamic memory allocation because we know n_instr only at run time rather than compile time
        int32_t* mem = new int32_t[n_instr];
        
        // input all instructions
        for (int idx_instr = 1; idx_instr <= n_instr; ++idx_instr){
            long instr;
            try{
                /* convert to long first to accept negative hexadecimal numbers, since we cannot input negative number right away into signed integer type int32_t
                 */
                if (!(std::cin >> std::hex >> instr)){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidInput();
                }
                
                // account for hexadecimals that might represent negative integers
                // 2^32 - 1 = (2^31 - 1) * 2 + 1
                // if input is greater than 0xffffffff, overflow has occurred.
                if (instr > static_cast<long>(std::numeric_limits<int>::max()) * 2 + 1){
                    throw Overflow();
                }

            } catch(InvalidInput& err) {
                std::cerr << "Invalid instruction: please input hexadecimal.\n";
                return 1;
            } catch(Overflow& error){
                std::cerr << "Invalid instruction (integer overflow): please input hexadecimal between 0x00000000 and 0xffffffff.\n";
                return 1;
            }
            
            // convert long to int32_t and store in mem array
            mem[idx_instr-1] = static_cast<int32_t>(instr);
        }  // end FOR loop for inputting instr into mem array
        
#ifdef DEBUG_MAIN
        for (int PC = 0; PC < n_instr; ++PC)
            std::cout << std::hex << mem[PC] << "\n";
#endif
        
        // fetch stored instructions from mem, decode into opcode and operand, execute corresponding stack functions.
        simulate(mem, n_instr);
        
        // free dynamically allocated memory after simulation mode is complete
        delete[] mem;
    }  // end if statement for entering simulation mode
    
    return 0;
}  // end of main() function


//#ifdef DEBUG_MAIN
//        Stack s1(6);
//        s1.push(1); s1.push(2); s1.push(3);
//        s1.print();
//        Stack s2;
//        s2.push(5); s2.push(4);
//        s2 = s1;
//        s1.pop(); s1.print();
//        s2.pop(); s2.print();
//#endif
        
//        std::shared_ptr<Stack> s1 = std::make_shared<Stack>(6);
//        s1->push(1); s1->push(2); s1->push(3);
//        s1->print();
//        std::shared_ptr<Stack> s2 = std::make_shared<Stack>();
//        s2 = s1;
//        s1->pop(); s1->print();
//        s2->pop(); s2->print();
