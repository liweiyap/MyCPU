#include <iostream>
#include "headers/std_input_parser.hpp"
#include "headers/exceptions.hpp"

// uncomment this block if wishing to debug
//#ifndef DEBUG_MAIN
//#define DEBUG_MAIN
//#endif

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
    
    // input number of instructions as integer
    char tmp_n_instr[11];
    std::cin >> tmp_n_instr;
    int n_instr;
    try{
        // check that there are no inputs like '10a', 'a10', or '10.0'
        n_instr = ConvertCharToPositiveInt(tmp_n_instr);
    } catch(InvalidInput& err) {
        std::cerr << "Invalid input: please try again. The number of instructions should be a positive integer.\n";
        return 1;
    }
    
#ifdef DEBUG_MAIN
    std::cout << n_instr << "\n";
#endif
    
    return 0;
}
