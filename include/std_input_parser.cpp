// uncomment this block if wishing to debug
/*
#ifndef DEBUG_HEX
#define DEBUG_HEX
#endif
 */

#include "std_input_parser.hpp"
#include "exceptions.hpp"

int ConvertCharToPositiveInt(const char text[]){
    int number = 0;
    
    for (int i = 0; i < strlen(text); ++i){
        if (!isdigit(text[i])) throw InvalidInput();
        
        number *= 10;
        number += (text[i] - '0');
    }
    
    return number;
}

bool IsValidHexadecimal(const char text[]){
    // check that first two chars are '0x' or '0X'
    if (int(text[0]) != 48) return false;
#ifdef DEBUG_HEX
    else std::cout << "passed check 0\n";
#endif
    
    if (int(text[1]) != 88 && int(text[1]) != 120) return false;
#ifdef DEBUG_HEX
    else std::cout << "passed check 1\n";
#endif
    
    if (strlen(text) > 10) return false;
#ifdef DEBUG_HEX
    else std::cout << "passed len check\n";
#endif
    
    // maximum int in hexademical notation is 0x7fffffff so first digit cannot be >=8
    if (int(text[2]) < 48 || int(text[2]) > 55) return false;
#ifdef DEBUG_HEX
    else std::cout << "passed check 2\n";
#endif
    
    for (int i = 3; i < strlen(text); ++i){
        // check if char is between '0' and '9' inclusive,
        //                          'A' and 'F' inclusive,
        //                       or 'a' and 'f' inclusive
        if ( (int(text[i]) < 48) ||
             (int(text[i]) > 57 && int(text[i]) < 65) ||
             (int(text[i]) > 70 && int(text[i]) < 97) ||
             (int(text[i]) > 102))
            return false;
#ifdef DEBUG_HEX
        else std::cout << "passed check " << i << "\n";
#endif
    }
    
    return true;
}
