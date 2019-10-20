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
    // dynamically allocate memory array
    int32_t* mem = new int32_t[n_instr];
    
    // set pointer of standard input to point to parameter istringstream
    std::streambuf* cin_old = std::cin.rdbuf(iss.rdbuf());
    
    // parse input stringstream into individual instructions and store in memory array
    long instr;
    for (int idx_instr = 1; idx_instr <= n_instr; ++idx_instr){
        std::cin >> std::hex >> instr;
        mem[idx_instr-1] = static_cast<int32_t>(instr);
    }
    
    // set pointer of standard output to point to some ostringstream
    std::ostringstream buffer;
    std::streambuf* cout_old = std::cout.rdbuf(buffer.rdbuf());
    
    // test the execution of either disassembly or simulation
    mode(mem, n_instr);
    
    // free dynamically allocated memory
    delete[] mem;
    
    // restore the respective pointers of standard output and input
    std::cin.rdbuf(cin_old);
    std::cout.rdbuf(cout_old);
    
    // return the stored output that wasn't streamed into standard output
    return buffer.str();
}  // end of function
