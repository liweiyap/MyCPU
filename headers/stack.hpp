/**
 * Definition of Node object, which is a building block of Stack object.
 * Declaration of Stack object for simulating CPU processes.
 */

#ifndef STACK_H
#define STACK_H
#pragma once

// uncomment this block if wishing to debug
/*
#ifndef DEBUG_STACK
#define DEBUG_STACK
#endif
 */

#include <iostream>
#include <cassert>
#include <algorithm>  // remove, swap
#include <memory>     // unique_ptr
#include <utility>    // move


/**
 * LIFO object used to simulate a virtual CPU.
 */
class Stack{
public:
    Stack();
    Stack(int v);
    void push(int v);
    void pop();
    int peek();
    int size();
    bool isEmpty();
    void print();
    void clear();
    ~Stack();
    
private:
    /**
     * Node object acts as building block for larger Stack object.
     * Each Node contains two attributes: its own value [int] and a pointer
     * that points either to NULL or the next Node in the same Stack.
     */
    struct Node{
        Node(int v): value(v){}
        Node(int v, std::unique_ptr<Node> n): value(v), next(std::move(n)){}
        int value;
        std::unique_ptr<Node> next;
    };
    
    std::unique_ptr<Node> top;
    int n_nodes = 0;
};

#endif
