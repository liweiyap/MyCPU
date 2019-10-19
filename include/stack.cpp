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
Stack::Stack(): top(0), n_nodes(0){}


/**
 * Constructor for Stack containing a single Node.
 *
 * @param node pointer to a Node
 * @return Stack with a single Node
 */
Stack::Stack(Node* node): top(node), n_nodes(1){}


/**
 * Constructor for Stack containing a single Node to be created for storing integer value
 *
 * @param v integer value for creating new Node object at top of Stack to be created
 * @return Stack with a single Node
 */
Stack::Stack(int v): top(new Node(v)), n_nodes(1){}


/**
 * Copy constructor
 *
 * @param s reference to another Stack
 * @return Stack
 */
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
}  // end of copy constructor


/**
 * Create new Node storing integer value.
 * Add said Node to top of Stack.
 *
 * @param v integer value for creating new Node to be pushed onto Stack
 */
void Stack::push(int v){
    Node* node = new Node(v, top);
    top = node;
    ++n_nodes;
}  // end of push function


/**
 * Add Node to top of Stack
 *
 * @overload
 * @param node pointer to Node to be pushed onto Stack
 */
void Stack::push(Node* node){
    node->next = top;
    top = node;
    ++n_nodes;
}  // end of overloaded push function


/**
 * Remove Node from top of Stack. Delete Node.
 */
void Stack::pop(){
    assert(!isEmpty() && "Error: pop() failed because stack is empty.");
    Node* node = top;
    top = top->next;
    delete node;
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
    Node* node = top;
    while (node){                             // while node != 0
        std::cout << node->value;
        if (node->next) std::cout << " -> ";  // if node->next != 0
        node = node->next;
    }
    std::cout << " ]\n";
}  // end of print function


/**
 * Assignment operator
 *
 * @param s reference to another Stack
 */
Stack& Stack::operator=(const Stack& s){
    if (top != s.top){               // no self-assignment
        Stack s_copy = s;            // create alias of s
        std::swap(top, s_copy.top);  // alias now has the garbage
    }                                // alias deconstruction; garbage cleaned up
    return *this;
}  // end of assignment operator


/**
 * Remove all Nodes from Stack. Delete all Nodes.
 */
void Stack::clear(){
    while (!isEmpty()){
        pop();
    }
}  // end of clear function


/**
 * Destructor
 */
Stack::~Stack(){
    clear();
}  // end of destructor
