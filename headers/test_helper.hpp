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

std::string general_test(void (*mode)(int32_t*, const int), std::istringstream& iss, const int n_instr);

#endif
