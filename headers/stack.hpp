/**
 * Definition of Node object, which is a building block of Stack object.
 * Declaration of Stack object for simulating CPU processes.
 */

#ifndef STACK_H
#define STACK_H
#pragma once

#include <iostream>
#include <cassert>
#include <algorithm>  // remove, swap


/**
 * Node object acts as building block for larger Stack object.
 * Each Node contains two attributes: its own value [int] and a pointer
 * that points either to NULL or the next Node in the same Stack.
 */
struct Node{
    // Inline constructor for stand-alone Node
    Node(int v): value(v), next(0){}
    
    // Inline constructor for Node object that points to another Node
    Node(int v, Node* n): value(v), next(n){}

    int value;
    Node* next;
};  // end of Node struct definition


/**
 * LIFO object used to simulate a virtual CPU.
 */
class Stack{
public:
    // Default constructor for empty Stack
    Stack();
    
    
    // Constructor for Stack containing a single Node
    Stack(Node* node);
    
    
    // Constructor for Stack containing a single Node to be created for storing integer value
    Stack(int v);
    
    
    // Copy constructor
    Stack(const Stack& s);
    
    
    // Create new Node storing integer value.
    // Add said Node to top of Stack.
    void push(int v);
    
    
    // Add Node to top of Stack
    void push(Node* node);
    
    
    // Remove Node from top of Stack. Delete Node.
    void pop();
    
    
    // Return int value stored in Node at the top without removing it from the Stack
    int peek();
    
    
    // Return total number of Nodes in Stack
    int size();
    
    
    // If true, Stack contains 0 Nodes. If false, Stack contains Nodes.
    bool isEmpty();
    
    
    // Print the value stored in all Nodes to standard output in the correct order.
    void print();
    
    
    // Assignment operator
    Stack& operator=(const Stack& s);
    
    
    // Remove all Nodes from Stack. Delete all Nodes.
    void clear();
    
    
    // Destructor
    ~Stack();
    
    
private:
    Node* top;
    
    int n_nodes;
};  // end of Stack class definition

#endif
