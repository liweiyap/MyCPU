#ifndef TEST_HELPER
#include "test_helper.hpp"
#endif

#include "catch.hpp"

TEST_CASE("simulate"){
    SECTION("Hello_world"){
        int n_instr = 23;
        
        std::istringstream iss("0x32000064 0x3200006c 0x32000072 0x3200006f 0x32000077 0x32000020 0x3200006f 0x3200006c 0x3200006c 0x32000065 0x32000048 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x1000000");
        
        REQUIRE( general_test(simulate, iss, n_instr) == "Hello world\n" );
    }  // end of section
}
