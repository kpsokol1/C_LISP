#pragma once
#ifndef LISP_LISPFUNCTION_H
#define LISP_LISPFUNCTION_H
#include "LispCallable.h"
#include "Stmt.h"
#include "Environment.h"

class LispFunction : public LispCallable{
public:
    LispFunction(const Function* declaration, Environment* closure);
    any call(Interpreter* interpreter, vector<any> arguments);
    int arity();
    string toString();
private:
    const Function* declaration;
    Environment* closure;               //fixme was const
};
#endif //LISP_LISPFUNCTION_H
