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
}


/**
 * Read a decimal integer value v from standard input, and push v onto operand stack.
 * Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 */
void in(Stack& S, unsigned int& PC){
    std::cout << "\nThe in() function has been called on the stack, which means that the hexadecimal of the corresponding instruction starts with '0x10'. Please input a decimal integer to proceed with the rest of the simulation:\n";
    
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
    
    S.push(v);
    ++PC;
}


/**
 * Read a character value v from standard input, and push v onto operand stack.
 * Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 */
void inchar(Stack& S, unsigned int& PC){
    std::cout << "\nThe inchar() function has been called on the stack, which means that the hexadecimal of the corresponding instruction starts with '0x11'. Please input a character to proceed with the rest of the simulation:\n";
    
    char v;
    std::cin >> std::dec >> v;
    S.push(int(v));
    ++PC;
}


/**
 * Pop the top value v from operand stack, and write v to standard output as decimal integer.
 * Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 */
void out(Stack& S, unsigned int& PC){
    int v = S.peek();
    S.pop();
    std::cout << std::dec << v;
    ++PC;
}


/**
 * Pop the top value v from operand stack, and write v to standard output as character.
 * Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 */
void outchar(Stack& S, unsigned int& PC){
    char v = static_cast<char>(S.peek());
    S.pop();
    std::cout << v;
    ++PC;
}


/**
 * Pop value r from operand stack. Pop value l from operand stack.
 * Push value l+r onto operand stack. Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of addition is greater than INT_MAX
 * @throws Underflow() exception thrown if result of addition is smaller than INT_MIN
 */
void add(Stack& S, unsigned int& PC){
    int r = S.peek();
    S.pop();
    
    int l = S.peek();
    S.pop();
    
    if (r > 0 && l > std::numeric_limits<int>::max() - r) throw Overflow();
    if (r < 0 && l < std::numeric_limits<int>::min() - r) throw Underflow();
    
    S.push(l+r);
    ++PC;
}


/**
 * Pop value r from operand stack. Pop value l from operand stack.
 * Push value l-r onto operand stack. Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of subtraction is greater than INT_MAX
 * @throws Underflow() exception thrown if result of subtraction is smaller than INT_MIN
 */
void sub(Stack& S, unsigned int& PC){
    int r = S.peek();
    S.pop();
    
    int l = S.peek();
    S.pop();
    
    if (r < 0 && l > std::numeric_limits<int>::max() + r) throw Overflow();
    if (r > 0 && l < std::numeric_limits<int>::min() + r) throw Underflow();
    
    S.push(l-r);
    ++PC;
}


/**
 * Pop value r from operand stack. Pop value l from operand stack.
 * Push value l*r onto operand stack. Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of multiplication is greater than INT_MAX
 * @throws Underflow() exception thrown if result of multiplication is smaller than INT_MIN
 */
void mul(Stack& S, unsigned int& PC){
    int r = S.peek();
    S.pop();
    
    int l = S.peek();
    S.pop();
    
    // Since INT_MAX = 2^31-1 and INT_MIN = -2^31, thus -INT_MIN > INT_MAX.
    if (l == -1 && r == std::numeric_limits<int>::min()) throw Overflow();
    if (r == -1 && l == std::numeric_limits<int>::min()) throw Overflow();
    if (r != 0 && l > std::numeric_limits<int>::max() / r) throw Overflow();
    if (r != 0 && l < std::numeric_limits<int>::min() / r) throw Underflow();
    
    S.push(l*r);
    ++PC;
}


/**
 * Pop value r from operand stack. Pop value l from operand stack.
 * Push value l/r (integer division) onto operand stack. Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of division is greater than INT_MAX
 * @throws DivisionByZero() exception thrown if denominator of division is equal to zero
 */
void div(Stack& S, unsigned int& PC){
    int r = S.peek();
    S.pop();
    
    int l = S.peek();
    S.pop();
    
    // Since INT_MAX = 2^31-1 and INT_MIN = -2^31, thus -INT_MIN > INT_MAX.
    if (r == -1 && l == std::numeric_limits<int>::min()) throw Overflow();
    if (r == 0) throw DivisionByZero();
    
    S.push(l/r);
    ++PC;
}


/**
 * Pop value r from operand stack. Pop value l from operand stack.
 * Push value l%r onto operand stack. Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of modulo is greater than INT_MAX
 * @throws DivisionByZero() exception thrown if denominator of division is equal to zero
 */
void mod(Stack& S, unsigned int& PC){
    int r = S.peek();
    S.pop();
    
    int l = S.peek();
    S.pop();
    
    // Since INT_MAX = 2^31-1 and INT_MIN = -2^31, thus -INT_MIN > INT_MAX.
    if (r == -1 && l == std::numeric_limits<int>::min()) throw Overflow();
    if (r == 0) throw DivisionByZero();
    
    S.push(l%r);
    ++PC;
}


/**
 * Pop value r from operand stack. Push value -r onto operand stack.
 * Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 * @throws Overflow() exception thrown if result of negation is greater than INT_MAX
 */
void neg(Stack& S, unsigned int& PC){
    int r = S.peek();
    S.pop();
    
    // Since INT_MAX = 2^31-1 and INT_MIN = -2^31, thus -INT_MIN > INT_MAX.
    if (r == std::numeric_limits<int>::min()) throw Overflow();
    
    S.push(-r);
    ++PC;
}


/**
 * Pop value r from operand stack. Push value r onto operand stack twice.
 * Then, increment program counter.
 *
 * @param S operand stack
 * @param PC program counter
 */
void dup(Stack& S, unsigned int& PC){
    int r = S.peek();
    S.push(r);
    ++PC;
}


/**
 * Pop value m from operand stack.
 * Push int32_t value r stored at memory location m onto operand stack.
 * Then, increment program counter.
 *
 * @param mem pointer to memory array of 32-bit signed integer values
 * @param S operand stack
 * @param PC program counter
 */
void load(int32_t* mem, Stack& S, unsigned int& PC){
    int m = S.peek();
    S.pop();
    
    int32_t r = mem[m];
    S.push(r);
    ++PC;
}


/**
 * Pop value m from operand stack. Pop value v from operand stack.
 * Store v at memory location m as int32_t.
 * Then, increment program counter.
 *
 * @param mem pointer to memory array of 32-bit signed integer values
 * @param S operand stack
 * @param PC program counter
 */
void store(int32_t* mem, Stack& S, unsigned int& PC){
    int m = S.peek();
    S.pop();
    
    int32_t v = static_cast<int32_t>(S.peek());
    S.pop();
    
    mem[m] = v;
    ++PC;
}


/**
 * Push value c onto operand stack. Then, increment program counter.
 *
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void const_c(const int c, Stack& S, unsigned int& PC){
    S.push(c);
    ++PC;
}


/**
 * Set program counter to value c.
 *
 * @param c signed integer operand decoded from input instruction
 * @param PC program counter
 */
void jmp_c(const int c, unsigned int& PC){
    PC = c;
}


/**
 * Jump if equal:
 * Pop value r from operand stack. Pop value l from operand stack.
 * If l == r, then set program counter to value c. Else, increment program counter.
 *
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void jeq_c(const int c, Stack& S, unsigned int& PC){
    int r = S.peek();
    S.pop();
    
    int l = S.peek();
    S.pop();
    
    if (l == r) PC = c;
    else ++PC;
}


/**
 * Jump if not equal:
 * Pop value r from operand stack. Pop value l from operand stack.
 * If l != r, then set program counter to value c. Else, increment program counter.
 *
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void jne_c(const int c, Stack& S, unsigned int& PC){
    int r = S.peek();
    S.pop();
    
    int l = S.peek();
    S.pop();
    
    if (l != r) PC = c;
    else ++PC;
}


/**
 * Jump if less:
 * Pop value r from operand stack. Pop value l from operand stack.
 * If l < r, then set program counter to value c. Else, increment program counter.
 *
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void jls_c(const int c, Stack& S, unsigned int& PC){
    int r = S.peek();
    S.pop();
    
    int l = S.peek();
    S.pop();
    
    if (l < r) PC = c;
    else ++PC;
}


/**
 * Jump if less or equal:
 * Pop value r from operand stack. Pop value l from operand stack.
 * If l <= r, then set program counter to value c. Else, increment program counter.
 *
 * @param c signed integer operand decoded from input instruction
 * @param S operand stack
 * @param PC program counter
 */
void jle_c(const int c, Stack& S, unsigned int& PC){
    int r = S.peek();
    S.pop();
    
    int l = S.peek();
    S.pop();
    
    if (l <= r) PC = c;
    else ++PC;
}
