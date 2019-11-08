/**
 * Definition of Stack object for simulating CPU processes.
 */

#ifndef STACK_H
#include "stack.hpp"
#endif


/**
 * Default constructor for empty Stack.
 *
 * @return empty Stack
 */
Stack::Stack(){}


/**
 * Constructor for Stack containing a single Node to be created for storing integer value
 *
 * @param v integer value for creating new Node object at top of Stack to be created
 * @return Stack with a single Node
 */
Stack::Stack(int v): top(std::make_unique<Node>(v)), n_nodes(1){}


/**
 * Create new Node storing integer value.
 * Add said Node to top of Stack.
 *
 * @param v integer value for creating new Node to be pushed onto Stack
 */
void Stack::push(int v){
    std::unique_ptr<Node> node = std::make_unique<Node>(v, std::move(top));
#ifdef DEBUG_STACK
    if (!top) std::cout << "top is now nullptr\n";
#endif
    top = std::move(node);
    ++n_nodes;
}  // end of push function


/**
 * Remove Node from top of Stack. Delete Node.
 */
void Stack::pop(){
    assert(!isEmpty() && "Error: pop() failed because stack is empty.");
    top = std::move(top->next);
    --n_nodes;
}  // end of pop function


/**
 * Return int value stored in Node at the top without removing it from the Stack.
 *
 * @return integer value stored in top Node of Stack
 */
int Stack::peek(){
    assert(!isEmpty() && "Error: peek() failed because stack is empty.");
    return top->value;
}  // end of peek function


/**
 * Return total number of Nodes in Stack.
 *
 * @return number of Nodes in Stack
 */
int Stack::size(){
    assert(n_nodes >= 0);
    return n_nodes;
}  // end of size function


/**
 * If true, Stack contains 0 Nodes. If false, Stack contains Nodes.
 *
 * @return boolean value for whether stack is empty
 */
bool Stack::isEmpty(){
    return !top;  // return top == 0
}  // end of isEmpty function


/**
 * Print the value stored in all Nodes to standard output in the correct order.
 */
void Stack::print(){
    std::cout << "[ ";
    std::unique_ptr<Node>* node = &top;
    while (*node){                             // while node != 0
        std::cout << (*node)->value;
        if ((*node)->next) std::cout << " -> ";  // if node->next != 0
        node = &(*node)->next;
    }
    std::cout << " ]\n";
}  // end of print function


/**
 * Remove all Nodes from Stack. Delete all Nodes.
 */
void Stack::clear(){
    top.reset();
    n_nodes = 0;
}  // end of clear function


/**
 * Destructor
 */
Stack::~Stack(){
    clear();
}  // end of destructor
