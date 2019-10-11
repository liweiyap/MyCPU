#include <iostream>

// uncomment this block if wishing to debug
//#ifndef DEBUG_MAIN
//#define DEBUG_MAIN
//#endif

// list of exceptions
class MyException{};
class InvalidInput: public MyException{};

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
    
    return 0;
}
