/**
 * list of exceptions that can be thrown in case of run-time errors
 */

#ifndef EXCEPTIONS
#define EXCEPTIONS
#pragma once

class MyException{};
class InvalidInput: public MyException{};
class Overflow: public MyException{};
class Underflow: public MyException{};
class DivisionByZero: public MyException{};
class MemOutOfBounds: public MyException{};

#endif
