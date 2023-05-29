#pragma once
#ifndef LISP_RUNTIMEERROR_H
#define LISP_RUNTIMEERROR_H
#include "TokenType.h"

using namespace std;
class RuntimeError{
public:
        const Token token;
        string message;
        RuntimeError(Token token, string message): message(message), token(token){}
};
#endif
