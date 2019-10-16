#include "headers/exceptions.hpp"
#include "headers/std_input_parser.hpp"
#include "headers/disassembly.hpp"

// uncomment this block if wishing to debug
/*
#ifndef DEBUG_MAIN
#define DEBUG_MAIN
#endif
 */

// TODO: fetch, decode, execute for simulator
// TODO: tests for disassembly input etc, stack, simulation input etc

struct Node{
    Node(int v): value(v), next(0){}
    Node(int v, Node* n): value(v), next(n){}

    int value;
    Node* next;
};

class Stack{
public:
    Stack(): top(0), n_nodes(0){}
    Stack(Node* node): top(node), n_nodes(1){}
    Stack(int v): top(new Node(v)), n_nodes(1){}
    Stack(const Stack& s): top(0), n_nodes(0){
        if (s.top == 0) return;
        
        top = new Node(s.top->value);
        ++n_nodes;
        
        Node* prev = top;
        for (Node* s_node = s.top->next; s_node != 0; s_node = s_node->next){
            Node* node = new Node(s_node->value);
            prev->next = node;
            prev = node;
            ++n_nodes;
        }
    }
    
    void push(int v){
        Node* node = new Node(v, top);
        top = node;
        ++n_nodes;
    }
    
    void push(Node* node){
        node->next = top;
        top = node;
        ++n_nodes;
    }
    
    void pop(){
        assert(!isEmpty() && "Error: pop() failed because stack is empty.");
        Node* node = top;
        top = top->next;
        delete node;
        --n_nodes;
    }
    
    int peek(){
        assert(!isEmpty() && "Error: peek() failed because stack is empty.");
        return top->value;
    }
    
    int size(){
        return n_nodes;
    }
    
    bool isEmpty(){
        return top == 0;
    }
    
    void print(){
        std::cout << "[ ";
        Node* node = top;
        while (node != 0){
            std::cout << node->value;
            if (node->next != 0) std::cout << " -> ";
            node = node->next;
        }
        std::cout << " ]\n";
    }
    
    Stack& operator=(const Stack& s){
        if (top != s.top){
            Stack s_copy = s;
            std::swap(top, s_copy.top);
        }
        return *this;
    }
    
    void clear(){
        while (!isEmpty()){
            pop();
        }
    }
    
    ~Stack(){
        clear();
    }
    
private:
    Node* top;
    int n_nodes;
};

int main(){
    // input first command as either "disassemble" or "simulate"
    char cmd[12];
    std::cin >> cmd;
    
    // throw exception if first command is neither "disassemble" nor "simulate"
    try{
        if (strcmp(cmd, "disassemble") && strcmp(cmd, "simulate")){
            throw InvalidInput();
        }
    } catch(InvalidInput& err) {
        std::cerr << "Invalid input: please try again. The first command must be either disassemble or simulate.\n";
        return 1;
    }
    
#ifdef DEBUG_MAIN
    if (strcmp(cmd, "disassemble") == 0) std::cout << "disassemble cmd received\n";
    if (strcmp(cmd, "simulate") == 0) std::cout << "simulate cmd received\n";
#endif
    
    // input number of instructions as positive integer
    char tmp_n_instr[11];
    std::cin >> tmp_n_instr;
    int n_instr;
    try{
        // check that there are no inputs like '10a', 'a10', '10.0', or '-10'
        n_instr = ConvertCharToPositiveInt(tmp_n_instr);
    } catch(InvalidInput& err) {
        std::cerr << "Invalid input: please try again. The number of instructions should be a positive integer.\n";
        return 1;
    }
    
#ifdef DEBUG_MAIN
    std::cout << n_instr << "\n";
#endif
    
    if (strcmp(cmd, "disassemble") == 0){
        // input all instructions
        for (int idx_instr = 1; idx_instr <= n_instr; ++idx_instr){
            /* receive instruction as char so that it is easier to filter out large
               hexadecimals that are larger than 0x7fffffff or invalid hexadecimals
               that contain characters like 'g'
             */
            char tmp_instr[256];
            std::cin >> std::hex >> tmp_instr;
            
            /* if we can detect early on that instruction is invalid, then just terminate
               right away and move on to the next instruction
             */
            if (!IsValidHexadecimal(tmp_instr)){
                std::cout << "data " << tmp_instr << "\n";
                continue;
            }
            
            // convert char (in hexidecimal form) to long to int (in decimal form)
            int instr = static_cast<int>(strtol(tmp_instr, NULL, 16));
            
            // disassemble instruction in decimal form into opcode and operand
            // print output according to opcode (and, where appropriate, operand)
            disassembly_std_output(instr);
        }
        
        std::cout << "end\n";
    }
    
    if (strcmp(cmd, "simulate") == 0){
        int32_t mem[n_instr];
        
        for (int idx_instr = 1; idx_instr <= n_instr; ++idx_instr){
            int32_t instr;
            std::cin >> std::hex >> instr;
            
            try{
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                    throw InvalidInput();
                }
            } catch(InvalidInput& err) {
                std::cerr << "Invalid instruction: please input hexadecimal between 0x00000000 and 0x7fffffff.\n";
                return 1;
            }
            
            mem[idx_instr-1] = instr;
        }
        
#ifdef DEBUG_MAIN
        for (int PC = 0; PC < n_instr; ++PC)
            std::cout << std::hex << mem[PC] << "\n";
#endif
        
        for (int PC = 0; PC < n_instr; ++PC){
            disassembled_instr d_instr = disassemble(mem[PC]);
            int opcode = d_instr.opcode;
            int operand = d_instr.operand;
            std::cout << "opcode = " << opcode << "\n";
            std::cout << "operand = " << operand << "\n";
        }
        
#ifdef DEBUG_MAIN
        Stack s1(6);
        s1.push(1); s1.push(2); s1.push(3);
        s1.print();
        Stack s2;
        s2.push(5); s2.push(4);
        s2 = s1;
        s1.pop(); s1.print();
        s2.pop(); s2.print();
#endif
    }
    
    return 0;
}
