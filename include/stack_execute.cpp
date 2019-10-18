#include "stack_execute.hpp"

void hlt(){
    return;
}

void in(Stack& S, int& PC){
    int v;
    std::cin >> std::dec >> v;
    S.push(v);
    ++PC;
}

void inchar(Stack& S, int& PC){
    char v;
    std::cin >> std::dec >> v;
    S.push(int(v));
    ++PC;
}

void out(Stack& S, int& PC){
    int v = S.peek();
    S.pop();
    std::cout << std::dec << v;
    ++PC;
}

void outchar(Stack& S, int& PC){
    char v = static_cast<char>(S.peek());
    S.pop();
    std::cout << v;
    ++PC;
}

void add(Stack& S, int& PC){
    int r = S.peek();
    S.pop();
    int l = S.peek();
    S.pop();
    if (r > 0 && l > std::numeric_limits<int>::max() - r) throw Overflow();
    if (r < 0 && l < std::numeric_limits<int>::min() - r) throw Underflow();
    S.push(l+r);
    ++PC;
}

void sub(Stack& S, int& PC){
    int r = S.peek();
    S.pop();
    int l = S.peek();
    S.pop();
    if (r < 0 && l > std::numeric_limits<int>::max() + r) throw Overflow();
    if (r > 0 && l < std::numeric_limits<int>::min() + r) throw Underflow();
    S.push(l-r);
    ++PC;
}

void mul(Stack& S, int& PC){
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

void div(Stack& S, int& PC){
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

void mod(Stack& S, int& PC){
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

void neg(Stack& S, int& PC){
    int r = S.peek();
    S.pop();
    // Since INT_MAX = 2^31-1 and INT_MIN = -2^31, thus -INT_MIN > INT_MAX.
    if (r == std::numeric_limits<int>::min()) throw Overflow();
    S.push(-r);
    ++PC;
}

void dup(Stack& S, int& PC){
    int r = S.peek();
    S.push(r);
    ++PC;
}

void load(int32_t* mem, Stack& S, int& PC){
    int m = S.peek();
    S.pop();
    int32_t r = mem[m];
    S.push(r);
    ++PC;
}

void store(int32_t* mem, Stack& S, int& PC){
    int m = S.peek();
    S.pop();
    int32_t v = static_cast<int32_t>(S.peek());
    S.pop();
    mem[m] = v;
    ++PC;
}

void const_c(const int c, Stack& S, int& PC){
    S.push(c);
    ++PC;
}

void jmp_c(const int c, int& PC){
    PC = c;
}

void jeq_c(const int c, Stack& S, int& PC){
    int r = S.peek();
    S.pop();
    int l = S.peek();
    S.pop();
    if (l == r) PC = c;
    else ++PC;
}

void jne_c(const int c, Stack& S, int& PC){
    int r = S.peek();
    S.pop();
    int l = S.peek();
    S.pop();
    if (l != r) PC = c;
    else ++PC;
}

void jls_c(const int c, Stack& S, int& PC){
    int r = S.peek();
    S.pop();
    int l = S.peek();
    S.pop();
    if (l < r) PC = c;
    else ++PC;
}

void jle_c(const int c, Stack& S, int& PC){
    int r = S.peek();
    S.pop();
    int l = S.peek();
    S.pop();
    if (l <= r) PC = c;
    else ++PC;
}
