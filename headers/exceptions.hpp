#ifndef EXCEPTIONS
#define EXCEPTIONS

#pragma once

// list of exceptions
class MyException{};
class InvalidInput: public MyException{};
class Overflow: public MyException{};
class Underflow: public MyException{};
class DivisionByZero: public MyException{};

#endif
