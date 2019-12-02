/**
 * helper function for aiding tests
 */

#ifndef TEST_HELPER
#include "test_helper.hpp"
#endif


/**
 * The disassembly and simulation modes both output to standard output.
 * Thus, to build tests for either modes, we save the produced output for a defined input
 * and compare it to the expected output.
 * We intend to use this function in the TEST_CASE object provided by the 'catch' header file.
 *
 * @param mode function that is either 'disassembly_std_output' or 'simulate'
 * @param iss input stringstream for storing predefined input containing hexadecimal instructions
 * @param n_instr total number of instructions
 * @return the output that would normally have been passed to standard output by 'disassembly_std_output' or 'simulate' in the form of a STL string
 */
std::string general_test(void (*mode)(int32_t*, const int), std::istringstream& iss, const int n_instr){
    int32_t* mem = new int32_t[n_instr];
    std::streambuf* cin_old = std::cin.rdbuf(iss.rdbuf());
    
    long instr;
    for (int idx_instr = 1; idx_instr <= n_instr; ++idx_instr){
        std::cin >> std::hex >> instr;
        mem[idx_instr-1] = static_cast<int32_t>(instr);
    }
    
    std::ostringstream buffer;
    std::streambuf* cout_old = std::cout.rdbuf(buffer.rdbuf());
    mode(mem, n_instr);
    
    delete[] mem;
    std::cin.rdbuf(cin_old);
    std::cout.rdbuf(cout_old);
    
    return buffer.str();
}
