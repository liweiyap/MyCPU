/**
 * list of functions for parsing/properly interpreting inputs from standard input
 */

// uncomment this block if wishing to debug
/*
#ifndef DEBUG_HEX
#define DEBUG_HEX
#endif
 */

#ifndef STD_INPUT_PARSER
#include "std_input_parser.hpp"
#endif


/**
 * converts an array of characters between '0' and '9' inclusive to a single positive integer
 *
 * @param text pointer to char between '0' and '9' inclusive
 * @return single integer value converted from array of char
 * @throws InvalidInput() exception thrown if none of the characters is between '0' and '9' inclusive
 * @throws Overflow() exception thrown if integer is greater than INT_MAX
 */
int ConvertCharToPositiveInt(const char* text){
    int number = 0;
    
    for (int i = 0; i < strlen(text); ++i){
        if (!isdigit(text[i])) throw InvalidInput();
        
        if (number > std::numeric_limits<int>::max() / 10) throw Overflow();
        number *= 10;
        
        if (number > std::numeric_limits<int>::max() - (text[i] - '0')) throw Overflow();
        number += (text[i] - '0');
    }
    
    return number;
}  // end of function
