#include "stack_execute.hpp"

void hlt(){
    return;
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
    S.push(l+r);
    ++PC;
}

void sub(Stack& S, int& PC){
    int r = S.peek();
    S.pop();
    int l = S.peek();
    S.pop();
    S.push(l-r);
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
