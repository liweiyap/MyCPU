/**
 * Functions required for disassembly mode
 */

#ifndef DISASSEMBLY
#include "disassembly.hpp"
#endif


/**
 * Each hexadecimal instruction is 8 x 4 = 32 bits long (each digit in a hexadecimal being a hex-nibble).
 * The first 2 x 4 = 8 bits are the opcode.
 * The last 6 x 4 = 24 bits are the operand.
 * In this function, we decode/split the instr into the opcode and operand.
 
 * The instr has been converted to decimal form, so to convert it back to
 * hexadecimal form, we have to divide by powers of 16. We only have to do
 * this twice because the remainder after two rounds of division is already
 * the operand, with the opcode also extracted during division.
 *
 * @param instr instruction that has been cast from its hexadecimal form at input to a decimal integer
 * @return struct containing opcode and operand decoded from instruction
 */
disassembled_instr disassemble(int instr){
    int idx_hex = 7;
    int opcode = 0;
    
    // only two rounds of division to get the first two digits as opcode
    while (idx_hex > 5){
        // instr is in decimal form. Convert it back to hexadecimal form
        opcode *= 10;
        int divisor = static_cast<int>(std::pow(16, idx_hex) + 0.5);
        opcode += (instr / divisor);
        instr %= divisor;
        --idx_hex;
    }
    int operand = instr;
    
    return disassembled_instr{opcode, operand};
}  // end of disassemble function


/**
 * Disassemble instruction in decimal form into opcode and operand.
 * Print output according to opcode (and, where appropriate, operand).
 */
void disassembly_std_output(int instr){
    disassembled_instr d_instr = disassemble(instr);
    int opcode = d_instr.opcode;
    int operand = d_instr.operand;
    
#ifdef DEBUG_DISASSEMBLY
    std::cout << "opcode = " << opcode << "\n";
    std::cout << "operand = " << operand << "\n";
#endif
    
    if (opcode == 1) std::cout << "hlt\n";
    else if (opcode == 10) std::cout << "in\n";
    else if (opcode == 11) std::cout << "inchar\n";
    else if (opcode == 12) std::cout << "out\n";
    else if (opcode == 13) std::cout << "outchar\n";
    else if (opcode == 20) std::cout << "add\n";
    else if (opcode == 21) std::cout << "sub\n";
    else if (opcode == 22) std::cout << "mul\n";
    else if (opcode == 23) std::cout << "div\n";
    else if (opcode == 24) std::cout << "mod\n";
    else if (opcode == 25) std::cout << "neg\n";
    else if (opcode == 26) std::cout << "dup\n";
    else if (opcode == 30) std::cout << "load\n";
    else if (opcode == 31) std::cout << "store\n";
    else if (opcode == 32) std::cout << "const " << std::dec << operand << "\n";
    else if (opcode == 40) std::cout << "jmp " << std::dec << operand << "\n";
    else if (opcode == 41) std::cout << "jeq " << std::dec << operand << "\n";
    else if (opcode == 42) std::cout << "jne " << std::dec << operand << "\n";
    else if (opcode == 43) std::cout << "jls " << std::dec << operand << "\n";
    else if (opcode == 44) std::cout << "jle " << std::dec << operand << "\n";
    else std::cout << "data 0x" << std::hex << instr << "\n";
}  // end of disassembly_std_output void function
