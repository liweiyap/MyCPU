#ifndef SIMULATION
#include "simulation.hpp"
#endif

#include "catch.hpp"
#include <sstream>

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
}

TEST_CASE("simulate"){
    SECTION("Hello_world"){
        int n_instr = 23;
        
        std::istringstream iss("0x32000064 0x3200006c 0x32000072 0x3200006f 0x32000077 0x32000020 0x3200006f 0x3200006c 0x3200006c 0x32000065 0x32000048 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x1000000");
        
        REQUIRE( general_test(simulate, iss, n_instr) == "Hello world\n" );
    }
}


