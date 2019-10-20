## Introduction

[`myCPU.cpp`](https://github.com/liweiyap/MyCPU/blob/master/myCPU.cpp) contains the `main()` function for simulating a stack-based CPU. The CPU contains an operand stack and a register, and it also has access to memory.
* The stack is used to store the results of computations during the processing of machine instructions. It is implemented as a FIFO object in the header file [`headers/stack.hpp`](https://github.com/liweiyap/MyCPU/blob/master/headers/stack.hpp).
* The register acts as a Program Counter (PC) that points to the address of the next machine instruction to be executed. It is implemented as an `unsigned int` in the helper file [`include/simulation.cpp`](https://github.com/liweiyap/MyCPU/blob/master/include/simulation.cpp).
* Machine instructions to be processed are first stored in a contiguous array in the memory. Each instruction is 32 bits wide; the first eight bits are the opcode and the last 24 bits are the operand that will eventually be stored on the stack. Each opcode will call one of the functions in the helper file [`include/stack_execute.cpp`](https://github.com/liweiyap/MyCPU/blob/master/include/stack_execute.cpp), which will execute a computation through the manipulation of the stack. The final result of the overall computation is written to the standard output after the final machine instruction is processed.

The `main()` function requires three types of variables from the standard input.
1. The type of mode: either `disassemble` or `simulate`.
2. The number of machine instructions to be stored in the memory as an array.
3. All machine instructions to be stored. Each instruction should be input as a hexadecimal but stored in the memory as a signed 32-bit integer (or `int32_t`). The first two hex-nibbles (or eight bits) of each hexadecimal represent the opcode, whilst the last six hex-nibbles (or 24 bits) represent the operand.

Depending on the type of mode, we get slightly different results written to the standard output. The disassembly mode translates all instructions in the memory array into a human-readable form so that we can understand each machine instruction. The simulation mode executes all the instructions in the memory array using the operand stack and the register.

## Example

Let's say that we wish to simulate the following C++ code:
```
int i = 10;
while (i != 0){
    std::cout << i;
    --i;
    std::cout << "\n";
}
```

## User Guide

Compilation of `myCPU.cpp` relies on the [CMake](https://cmake.org/) build system. The code has been tested with recent versions of the [Clang](http://clang.llvm.org/docs/) C++ compiler. To compile and run, execute the following on the command line, starting in the root of the repository:
```
mkdir build
cd build
cmake ..
make all
./myCPU
```
