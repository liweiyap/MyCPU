## Introduction

[`myCPU.cpp`](https://github.com/liweiyap/MyCPU/blob/master/myCPU.cpp) contains the `main()` function for simulating a stack-based CPU. The CPU contains an operand stack and a register, and it also has access to memory.
* The stack is used to store the results of computations during the processing of machine instructions. It is implemented as a LIFO object in the header file [`headers/stack.hpp`](https://github.com/liweiyap/MyCPU/blob/master/headers/stack.hpp).
* The register acts as a Program Counter (PC) that points to the address of the next machine instruction to be executed. It is implemented as an `unsigned int` in the helper file [`include/simulation.cpp`](https://github.com/liweiyap/MyCPU/blob/master/include/simulation.cpp).
* Machine instructions to be processed are first stored in a contiguous array in the memory. Each instruction is 32 bits wide; the first eight bits are the opcode and the last 24 bits are the operand that will eventually be stored on the stack. Each opcode will call one of the functions in the helper file [`include/stack_execute.cpp`](https://github.com/liweiyap/MyCPU/blob/master/include/stack_execute.cpp), which will execute a computation through the manipulation of the stack. The results of some of the computations may be written to the standard output until the final machine instruction is processed.

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
std::cout << "\n";
```

To simulate this code, we input the following when running the `main()` function in [`myCPU.cpp`](https://github.com/liweiyap/MyCPU/blob/master/myCPU.cpp):
```
simulate
16
0x3200000f
0x30000000
0x26000000
0x26000000
0x32000000
0x4100000e
0x12000000
0x32000001
0x21000000
0x3200000f
0x31000000
0x3200000a
0x13000000
0x40000000
0x1000000
0xa
```

As expected, this will return the following output:
```
10
9
8
7
6
5
4
3
2
1

```

To understand how [`myCPU.cpp`](https://github.com/liweiyap/MyCPU/blob/master/myCPU.cpp) has simulated the C++ code, we can re-run the same inputs -- but this time with `disassemble` rather than `simulate`. This will then call the helper functions in the file [`include/disassembly.cpp`](https://github.com/liweiyap/MyCPU/blob/master/include/disassembly.cpp). Below, we show again the inputs, but this time with the output of the `disassemble` mode as comments on the right hand side.
```
disassemble  // OUTPUT OF DISASSEMBLY AS COMMENTS   |   MEANING IN C++
16           // ------------------------------------|-------------------------
0x3200000f   // const   15  ;   load i for ...      |
0x30000000   // load        ;   ... decrement       |
0x26000000   // dup         ;   ... output          |
0x26000000   // dup         ;   ... test            |   int i = 10;
0x32000000   // const    0  ;   if i == 0           |   while (i != 0){
0x4100000e   // jeq     14  ;     jump to halt      |
0x12000000   // out         ;   output i            |       std::cout << i;
0x32000001   // const    1  ;   decrement i         |       --i;
0x21000000   // sub         ;                       |
0x3200000f   // const   15  ;                       |
0x31000000   // store       ;   store i             |
0x3200000a   // const   10  ;   output newline      |       std::cout << "\n";
0x13000000   // outchar     ;                       |
0x40000000   // jmp      0  ;   jump to start       |   }
0x1000000    // hlt         ;   stop program        |
0xa          // data   0xa  ;   variable i          |
             // end                                 |   std::cout << "\n";
```

More test cases can be found in [`tests/myCPU_tests.cpp`](https://github.com/liweiyap/MyCPU/blob/master/tests/myCPU_tests.cpp).

## Compilation

To create a local copy of this repository, simply click 'Download'. Alternatively, clone it by first navigating to the path you want to store the local copy and then executing the following on the command line:
```
git clone git@github.com:liweiyap/MyCPU.git
```

Compilation relies on the [CMake](https://cmake.org/) build system. The code has been tested with recent versions of the [Clang](http://clang.llvm.org/docs/) C++ compiler. To compile and run, execute the following **in the root of the repository**:
```
mkdir build
cd build
cmake ..
make all
./myCPU
```

After executing `make all`, we can also run the test cases:
```
./tests/myCPU_tests
```

## Credits

Full credits for the header file [`headers/catch.hpp`](https://github.com/liweiyap/MyCPU/blob/master/headers/catch.hpp) go to the authors of [Catch2](https://github.com/catchorg/Catch2). This allows for easy testing in [`tests/myCPU_tests.cpp`](https://github.com/liweiyap/MyCPU/blob/master/tests/myCPU_tests.cpp) by using a header-only library.

This repository was inspired by a coursework from a prerequisite course called Informatik I in the first semester of my master's studies in computational biology. The lecturer of this course was [Prof. Felix Friedrich](http://people.inf.ethz.ch/felixf/index.html).
