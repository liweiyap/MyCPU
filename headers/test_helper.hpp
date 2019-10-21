/**
 * helper function for aiding tests
 */

#ifndef TEST_HELPER
#define TEST_HELPER
#pragma once

#ifndef SIMULATION
#include "simulation.hpp"
#endif

#include <sstream>    // istringstream, ostringstream
#include <streambuf>  // streambuf


/**
 * The disassembly and simulation modes both output to standard output.
 * Thus, to build tests for either modes, we save the produced output for a defined input
 * and compare it to the expected output.
 * We intend to use this function in the TEST_CASE object provided by the 'catch' header file.
 *
 * @param mode function that is either 'disassembly_std_output' or 'simulate'
 * @param iss input stringstream for storing predefined input containing hexadecimal instructions
 * @param n_instr total number of instructions
 * @return the output that would normally have been passed to standard output by 'disassembly_std_output' or 'simulate' in the form of an STL string
 */
std::string general_test(void (*mode)(int32_t*, const int), std::istringstream& iss, const int n_instr);


#endif
