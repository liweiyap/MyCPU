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
#include <limits>    // numeric_limits

int ConvertCharToPositiveInt(const char* text);

#endif
