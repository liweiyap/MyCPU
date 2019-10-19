#ifndef STACK_H
#include "stack.hpp"
#endif

// Default constructor for empty Stack
Stack::Stack(): top(0), n_nodes(0){}

// Constructor for Stack containing a single Node
Stack::Stack(Node* node): top(node), n_nodes(1){}

// Constructor for Stack containing a single Node to be created for storing integer value
Stack::Stack(int v): top(new Node(v)), n_nodes(1){}

// Copy constructor
Stack::Stack(const Stack& s): top(0), n_nodes(0){
    if (!s.top) return;  // if s.top == 0
    
    top = new Node(s.top->value);
    ++n_nodes;
    
    Node* prev = top;
    for (Node* s_node = s.top->next; s_node; s_node = s_node->next){  // while s_node != 0
        Node* node = new Node(s_node->value);
        prev->next = node;
        prev = node;
        ++n_nodes;
    }
}

// Create new Node storing integer value.
// Add said Node to top of Stack.
void Stack::push(int v){
    Node* node = new Node(v, top);
    top = node;
    ++n_nodes;
}

// Add Node to top of Stack
void Stack::push(Node* node){
    node->next = top;
    top = node;
    ++n_nodes;
}

// Remove Node from top of Stack. Delete Node.
void Stack::pop(){
    assert(!isEmpty() && "Error: pop() failed because stack is empty.");
    Node* node = top;
    top = top->next;
    delete node;
    --n_nodes;
}

// Return int value stored in Node at the top without removing it from the Stack
int Stack::peek(){
    assert(!isEmpty() && "Error: peek() failed because stack is empty.");
    return top->value;
}

// Return total number of Nodes in Stack
int Stack::size(){
    return n_nodes;
}

// If true, Stack contains 0 Nodes. If false, Stack contains Nodes.
bool Stack::isEmpty(){
    return !top;  // return top == 0
}

// Print the value stored in all Nodes to standard output in the correct order.
void Stack::print(){
    std::cout << "[ ";
    Node* node = top;
    while (node){                             // while node != 0
        std::cout << node->value;
        if (node->next) std::cout << " -> ";  // if node->next != 0
        node = node->next;
    }
    std::cout << " ]\n";
}

// Assignment operator
Stack& Stack::operator=(const Stack& s){
    if (top != s.top){               // no self-assignment
        Stack s_copy = s;            // create alias of s
        std::swap(top, s_copy.top);  // alias now has the garbage
    }                                // alias deconstruction; garbage cleaned up
    return *this;
}

// Remove all Nodes from Stack. Delete all Nodes.
void Stack::clear(){
    while (!isEmpty()){
        pop();
    }
}

// Destructor
Stack::~Stack(){
    clear();
}
