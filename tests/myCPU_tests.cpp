#ifndef TEST_HELPER
#include "test_helper.hpp"
#endif

#include "catch.hpp"


// test disassembly mode
TEST_CASE("disassemble"){
    /*
     This test is equivalent to the commented disassembly of:
     
     std::cout << "Hello world\n";
     */
    SECTION("Hello_world"){
        int n_instr = 23;
        
        std::istringstream iss("0x32000064 0x3200006c 0x32000072 0x3200006f 0x32000077 0x32000020 0x3200006f 0x3200006c 0x3200006c 0x32000065 0x32000048 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x1000000");
        
        REQUIRE( general_test(disassembly_std_output, iss, n_instr) == "const 100\nconst 108\nconst 114\nconst 111\nconst 119\nconst 32\nconst 111\nconst 108\nconst 108\nconst 101\nconst 72\noutchar\noutchar\noutchar\noutchar\noutchar\noutchar\noutchar\noutchar\noutchar\noutchar\noutchar\nhlt\nend\n" );
    }  // end of "Hello_world" section
    
    
    /*
     This test is equivalent to the commented disassembly of:
     
     int i = 0;
     while (i != 9){
         ++i;
         std::cout << i;
     }
     */
    SECTION("WHILE_Loop"){
        int n_instr = 10;
        
        std::istringstream iss("0x32000000 0x32000001 0x20000000 0x26000000 0x26000000 0x12000000 0x32000009 0x41000009 0x40000001 0x1000000");
        
        REQUIRE( general_test(disassembly_std_output, iss, n_instr) == "const 0\nconst 1\nadd\ndup\ndup\nout\nconst 9\njeq 9\njmp 1\nhlt\nend\n" );
    }  // end of "WHILE_Loop" section
    
    
    /*
     This test is equivalent to simulating the storing of a variable in a specific memory location
     and then retrieving it later and writing it to standard output.
     */
    SECTION("store_and_load"){
        int n_instr = 7;
        
        std::istringstream iss("0x320000ff 0x32000100 0x31000000 0x32000100 0x30000000 0x12000000 0x1000000");
        
        REQUIRE( general_test(disassembly_std_output, iss, n_instr) == "const 255\nconst 256\nstore\nconst 256\nload\nout\nhlt\nend\n" );
    }  // end of "store_and_load" section
    
}  // end of "disassembly" TEST_CASE


// test simulation mode
TEST_CASE("simulate"){
    /*
     This test is equivalent to simulating:
     
     std::cout << "Hello world\n";
     */
    SECTION("Hello_world"){
        int n_instr = 23;
        
        std::istringstream iss("0x32000064 0x3200006c 0x32000072 0x3200006f 0x32000077 0x32000020 0x3200006f 0x3200006c 0x3200006c 0x32000065 0x32000048 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x13000000 0x1000000");
        
        REQUIRE( general_test(simulate, iss, n_instr) == "Hello world\n" );
    }  // end of "Hello_world" section
    
    
    /*
     This test is equivalent to simulating:
     
     int i = 0;
     while (i != 9){
         ++i;
         std::cout << i;
     }
     */
    SECTION("WHILE_Loop"){
        int n_instr = 10;
        
        std::istringstream iss("0x32000000 0x32000001 0x20000000 0x26000000 0x26000000 0x12000000 0x32000009 0x41000009 0x40000001 0x1000000");
        
        REQUIRE( general_test(simulate, iss, n_instr) == "123456789\n" );
    }  // end of "WHILE_Loop" section
    
    
    /*
     This test is equivalent to simulating the storing of a variable in a specific memory location
     and then retrieving it later and writing it to standard output.
     */
    SECTION("store_and_load"){
        int n_instr = 7;
        
        std::istringstream iss("0x320000ff 0x32000100 0x31000000 0x32000100 0x30000000 0x12000000 0x1000000");
        
        REQUIRE( general_test(simulate, iss, n_instr) == "255\n" );
    }  // end of "store_and_load" section
    
}  // end of "simulate" TEST_CASE


// just a simple test on sample stack operations, including alternative constructor, assignment operator, push, pop, and print
TEST_CASE("stack", "sample_test"){
    // set pointer of standard output to point to some ostringstream
    std::ostringstream buffer;
    std::streambuf* cout_old = std::cout.rdbuf(buffer.rdbuf());
    
    Stack s1(6);
    s1.push(1); s1.push(2); s1.push(3);
    s1.print();
    
    REQUIRE( buffer.str() == "[ 3 -> 2 -> 1 -> 6 ]\n" );
    buffer.str("");
    
    Stack s2;
    s2.push(5); s2.push(4);
    s2 = s1;
    s2.pop(); s2.print();
    
    REQUIRE( buffer.str() == "[ 2 -> 1 -> 6 ]\n" );
    
    // restore the respective pointers of standard output and input
    std::cout.rdbuf(cout_old);
}  // end of "stack" TEST_CASE
