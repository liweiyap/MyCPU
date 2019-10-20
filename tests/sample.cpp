//#include "catch.hpp"

#ifndef SIMULATION
#include "simulation.hpp"
#endif

#include <sstream>

//TEST_CASE("simulate"){
//    SECTION("23"){
//        int32_t* mem = new int32_t[23];
//
//        std::istringstream iss("1 a 1 b 4 a 4 b 9");
//
//        delete[] mem;
//    }
//}

int main(){
    int32_t* mem = new int32_t[23];
    
    std::istringstream iss("0x32000064 0x3200006c 0x32000072 0x3200006f 0x32000077 0x32000020 0x3200006f 0x3200006c 0x3200006c 0x32000065 0x32000048 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x1000000");
    
    // set pointer of standard input to point to istringstreams
    std::cin.rdbuf(iss.rdbuf());
    
    long instr;
    for (int idx_instr = 1; idx_instr <= 23; ++idx_instr){
        std::cin >> std::hex >> instr;
        mem[idx_instr-1] = static_cast<int32_t>(instr);
    }
    
    simulate(mem, 23);
    
    delete[] mem;
}
