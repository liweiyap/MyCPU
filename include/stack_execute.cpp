/**
 * List of possible functions that can be executed on the stack
 * according to decoded instructions during simulation.
 */

#ifndef STACK_EXECUTE
#include "stack_execute.hpp"
#endif

/**
 * just wanted a function that was called hlt() to make the simulation mode complete.
 * This fn doesn't actually do anything. The halting of the system and the exit from
 * the simulation mode is instead done in the simulate() function when the corr.
 * opcode reaches a value of 1.
 */
void hlt(){
    return;
}  // end of hlt function


/**
 * @param S operand stack
 * @param PC program counter
 */
void in(Stack& S, int& PC){
    // read a decimal integer value v from standard input
    char tmp_v[12];
    std::cin >> std::dec >> tmp_v;
    int v;
    
    // check that there are no inputs like '10a', 'a10', or '10.0'
    if (tmp_v[0] == '-'){
        auto neg_v = std::remove(std::begin(tmp_v), std::begin(tmp_v) + 2, '-');
        v = -(ConvertCharToPositiveInt(neg_v));
    } else{
        v = ConvertCharToPositiveInt(tmp_v);
    }
    
    // push v onto operand stack
    S.push(v);
    
    // increment program counter
    ++PC;
}  // end of in function


/**
 * @param S operand stack
 * @param PC program counter
 */
void inchar(Stack& S, int& PC){
    // read a character value v from standard input
    char v;
    std::cin >> std::dec >> v;
    
    // push v onto operand stack
    S.push(int(v));
    
    // increment program counter
    ++PC;
}  // end of inchar function


/**
 * @param S operand stack
 * @param PC program counter
 */
void out(Stack& S, int& PC){
    // pop value v from operand stack
    int v = S.peek();
    S.pop();
    
    // write v to standard output as decimal integer
    std::cout << std::dec << v;
    
    // increment program counter
    ++PC;
}  // end of out function


/**
 * @param S operand stack
 * @param PC program counter
 */
void outchar(Stack& S, int& PC){
    // pop value v from operand stack
    char v = static_cast<char>(S.peek());
    S.pop();
    
    // write v to standard output as character
    std::cout << v;
    
    // increment program counter
    ++PC;
}  // end of outchar function


/**
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of addition is greater than INT_MAX
 * @throws Underflow() exception thrown if result of addition is smaller than INT_MIN
 */
void add(Stack& S, int& PC){
    // pop value r from operand stack
    int r = S.peek();
    S.pop();
    
    // pop value l from operand stack
    int l = S.peek();
    S.pop();
    
    // check for overflows and underflows
    if (r > 0 && l > std::numeric_limits<int>::max() - r) throw Overflow();
    if (r < 0 && l < std::numeric_limits<int>::min() - r) throw Underflow();
    
    // if no overflow or underflow, push value l+r onto operand stack
    S.push(l+r);
    
    // increment program counter
    ++PC;
}  // end of add function


/**
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of subtraction is greater than INT_MAX
 * @throws Underflow() exception thrown if result of subtraction is smaller than INT_MIN
 */
void sub(Stack& S, int& PC){
    // pop value r from operand stack
    int r = S.peek();
    S.pop();
    
    // pop value l from operand stack
    int l = S.peek();
    S.pop();
    
    // check for overflows and underflows
    if (r < 0 && l > std::numeric_limits<int>::max() + r) throw Overflow();
    if (r > 0 && l < std::numeric_limits<int>::min() + r) throw Underflow();
    
    // if no overflow or underflow, push value l-r onto operand stack
    S.push(l-r);
    
    // increment program counter
    ++PC;
}  // end of sub function


/**
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of multiplication is greater than INT_MAX
 * @throws Underflow() exception thrown if result of multiplication is smaller than INT_MIN
 */
void mul(Stack& S, int& PC){
    // pop value r from operand stack
    int r = S.peek();
    S.pop();
    
    // pop value l from operand stack
    int l = S.peek();
    S.pop();
    
    // check for overflows and underflows
    // Since INT_MAX = 2^31-1 and INT_MIN = -2^31, thus -INT_MIN > INT_MAX.
    if (l == -1 && r == std::numeric_limits<int>::min()) throw Overflow();
    if (r == -1 && l == std::numeric_limits<int>::min()) throw Overflow();
    if (r != 0 && l > std::numeric_limits<int>::max() / r) throw Overflow();
    if (r != 0 && l < std::numeric_limits<int>::min() / r) throw Underflow();
    
    // if no overflow or underflow, push value l*r onto operand stack
    S.push(l*r);
    
    // increment program counter
    ++PC;
}  // end of mul function


/**
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of division is greater than INT_MAX
 * @throws DivisionByZero() exception thrown if denominator of division is equal to zero
 */
void div(Stack& S, int& PC){
    // pop value r from operand stack
    int r = S.peek();
    S.pop();
    
    // pop value l from operand stack
    int l = S.peek();
    S.pop();
    
    // check for overflow and division by zero
    // Since INT_MAX = 2^31-1 and INT_MIN = -2^31, thus -INT_MIN > INT_MAX.
    if (r == -1 && l == std::numeric_limits<int>::min()) throw Overflow();
    if (r == 0) throw DivisionByZero();
    
    // if no overflow or division by zero, push value l/r onto operand stack
    S.push(l/r);
    
    // increment program counter
    ++PC;
}  // end of div function


/**
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of modulo is greater than INT_MAX
 * @throws DivisionByZero() exception thrown if denominator of division is equal to zero
 */
void mod(Stack& S, int& PC){
    // pop value r from operand stack
    int r = S.peek();
    S.pop();
    
    // pop value l from operand stack
    int l = S.peek();
    S.pop();
    
    // check for overflow and division by zero
    // Since INT_MAX = 2^31-1 and INT_MIN = -2^31, thus -INT_MIN > INT_MAX.
    if (r == -1 && l == std::numeric_limits<int>::min()) throw Overflow();
    if (r == 0) throw DivisionByZero();
    
    // if no overflow or division by zero, push value l%r onto operand stack
    S.push(l%r);
    
    // increment program counter
    ++PC;
}  // end of mod function


/**
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of negation is greater than INT_MAX
 */
void neg(Stack& S, int& PC){
    // pop value r from operand stack
    int r = S.peek();
    S.pop();
    
    // check for overflow
    // Since INT_MAX = 2^31-1 and INT_MIN = -2^31, thus -INT_MIN > INT_MAX.
    if (r == std::numeric_limits<int>::min()) throw Overflow();
    
    // if no overflow, push value -r onto operand stack
    S.push(-r);
    
    // increment program counter
    ++PC;
}  // end of neg function


/**
 * @param S operand stack
 * @param PC program counter
 */
void dup(Stack& S, int& PC){
    // pop value r from operand stack and push it back onto operand stack twice
    int r = S.peek();
    S.push(r);
    
    // increment program counter
    ++PC;
}  // end of dup function


/**
 * @param mem pointer to memory array of 32-bit signed integer values
 * @param S operand stack
 * @param PC program counter
 */
void load(int32_t* mem, Stack& S, int& PC){
    // pop value m from operand stack
    int m = S.peek();
    S.pop();
    
    // push int32_t value r stored at memory location m to operand stack
    int32_t r = mem[m];
    S.push(r);
    
    // increment program counter
    ++PC;
}  // end of load function


/**
 * @param mem pointer to memory array of 32-bit signed integer values
 * @param S operand stack
 * @param PC program counter
 */
void store(int32_t* mem, Stack& S, int& PC){
    // pop value m from operand stack
    int m = S.peek();
    S.pop();
    
    // pop value v from operand stack as an int32_t
    int32_t v = static_cast<int32_t>(S.peek());
    S.pop();
    
    // store v at memory location m
    mem[m] = v;
    
    // increment program counter
    ++PC;
}  // end of store function


/**
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void const_c(const int c, Stack& S, int& PC){
    // push value c onto operand stack
    S.push(c);
    
    // increment program counter
    ++PC;
}  // end of const_c function


/**
 * @param c signed integer operand decoded from input instruction
 * @param PC program counter
 */
void jmp_c(const int c, int& PC){
    // set program counter to value c
    PC = c;
}  // end of jmp_c function


/**
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void jeq_c(const int c, Stack& S, int& PC){
    // pop value r from operand stack
    int r = S.peek();
    S.pop();
    
    // pop value l from operand stack
    int l = S.peek();
    S.pop();
    
    // if l == r, then let program counter jump to value c
    // otherwise, increment program counter
    if (l == r) PC = c;
    else ++PC;
}  // end of jeq_c function


/**
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void jne_c(const int c, Stack& S, int& PC){
    // pop value r from operand stack
    int r = S.peek();
    S.pop();
    
    // pop value l from operand stack
    int l = S.peek();
    S.pop();
    
    // if l != r, then let program counter jump to value c
    // otherwise, increment program counter
    if (l != r) PC = c;
    else ++PC;
}  // end of jne_c function


/**
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void jls_c(const int c, Stack& S, int& PC){
    // pop value r from operand stack
    int r = S.peek();
    S.pop();
    
    // pop value l from operand stack
    int l = S.peek();
    S.pop();
    
    // if l < r, then let program counter jump to value c
    // otherwise, increment program counter
    if (l < r) PC = c;
    else ++PC;
}  // end of jls_c function


/**
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void jle_c(const int c, Stack& S, int& PC){
    // pop value r from operand stack
    int r = S.peek();
    S.pop();
    
    // pop value l from operand stack
    int l = S.peek();
    S.pop();
    
    // if l <= r, then let program counter jump to value c
    // otherwise, increment program counter
    if (l <= r) PC = c;
    else ++PC;
}  // end of jle_c function
