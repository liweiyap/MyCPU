#include <iostream>
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
