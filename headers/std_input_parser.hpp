/**
 * list of functions for parsing/properly interpreting inputs from standard input
 */

#ifndef STD_INPUT_PARSER
#define STD_INPUT_PARSER
#pragma once

#ifndef EXCEPTIONS
#include "exceptions.hpp"
#endif

#include <iostream>


/**
 * converts an array of characters between '0' and '9' inclusive to a single positive integer
 *
 * @param text pointer to char between '0' and '9' inclusive
 * @return single integer value converted from array of char
 * @throws InvalidInput() exception thrown if none of the characters is between '0' and '9' inclusive
 * @throws Overflow() exception thrown if integer is greater than INT_MAX
 */
int ConvertCharToPositiveInt(const char* text);


#endif
