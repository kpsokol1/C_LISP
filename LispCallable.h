#pragma once
#ifndef LISP_LISPCALLABLE_H
#define LISP_LISPCALLABLE_H
#include "global.h"
#include <vector>
using namespace std;

class Interpreter;
class LispCallable{
public:
    virtual int arity() = 0;
    virtual any call(Interpreter* interpreter, vector<any> arguments) = 0;
};
#endif //LISP_LISPCALLABLE_H
