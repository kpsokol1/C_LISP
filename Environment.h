#pragma once
#ifndef LISP_ENVIRONMENT_H
#define LISP_ENVIRONMENT_H
#include "global.h"
#include "TokenType.h"

using namespace std;
class Environment{
public:
    Environment();

    Environment(Environment* enclosing);

    void define(const string name, const any value);

    any get(Token name);

    Environment* ancestor(int distance);

    void assign(Token name, any value);

    Environment* enclosing;

    unordered_map<string, any> values;
private:

};
#endif //LISP_ENVIRONMENT_H
