#pragma once
#ifndef LISP_EXPR_H
#define LISP_EXPR_H
#include <iostream>
#include "global.h"
#include "TokenType.h"
#include <vector>

using namespace std;

//prototypes
class Binary;
class Expr;
class Visitor;
class Literal;
class Unary;
class Variable;
class Logical;
class Call;
class List;
class ListElement;

class Nil;
class Number;
class Symbol;
class If;

class Visitor{          //equivalent to visitor interface
public:
    virtual any visitBinaryExpr(const Binary* expr) = 0;
    virtual any visitLiteralExpr(const Literal* expr) = 0;
    virtual any visitNumberExpr(const Number* expr) = 0;
    virtual any visitSymbolExpr(const Symbol* expr) = 0;
    virtual any visitUnaryExpr(const Unary* expr) = 0;
    virtual any visitVariableExpr(const Variable* expr) = 0;
    virtual any visitLogicalExpr(const Logical* expr) = 0;
    virtual any visitNilExpr(const Nil* expr) = 0;

    virtual any visitCallExpr(const Call* expr) = 0;
    virtual any visitListExpr(const List* expr) = 0;
    virtual any visitListElementExpr(const ListElement* expr) = 0;
    virtual any visitIfExpr(const If* expr) = 0;
};
class Expr{
public:
    virtual any accept(Visitor* visitor) const = 0;
};

class Binary: public Expr{
public:
    const Expr* left;
    const Token _operator;
    const Expr* right;

    Binary(Expr* left, Token _operator, Expr* right): left(left), _operator(_operator), right(right){}
    any accept(Visitor* visitor) const override {return visitor->visitBinaryExpr(this);}
};

class Literal: public Expr{ //basically will only be used for numbers
public:
    const any value;
    const string stringValue;
    Literal(any value, string stringValue):value(value), stringValue(stringValue){}
    any accept(Visitor* visitor) const override {return visitor->visitLiteralExpr(this);}
};

class Number: public Expr{ //basically will only be used for numbers
public:
    const any value;
    const string stringValue;
    Number(any value, string stringValue):value(value), stringValue(stringValue){}
    any accept(Visitor* visitor) const override {return visitor->visitNumberExpr(this);}
};

class Symbol: public Expr{
public:
    const any value;
    const string stringValue;
    Symbol(any value, string stringValue):value(value), stringValue(stringValue){}
    any accept(Visitor* visitor) const override {return visitor->visitSymbolExpr(this);}

};

class Logical: public Expr{                     //essentially the same as the binary class but the operato is a logical operator instead of a binary operator
public:
    const Expr* left;
    const Token _operator;
    const Expr* right;

    Logical(Expr* left, Token _operator, Expr* right): left(left), _operator(_operator), right(right){}
    any accept(Visitor* visitor) const override {return visitor->visitLogicalExpr(this);}
};

class Unary: public Expr{           //we will use for like car and cdr etc
public:
    const Token _operator;
    const Expr* right;
    Unary(Token _operator, Expr* right):_operator(_operator), right(right){}
    any accept(Visitor* visitor) const override {return visitor->visitUnaryExpr(this);}
};

class Variable: public Expr{
public:
    const Token name;
    Variable(Token name): name(name){}
    any accept(Visitor* visitor) const override {return visitor->visitVariableExpr(this);}
};

class Call: public Expr{
public:
    const Token functionName;
    vector<Expr*> arguments;
    Call(Token functionName, vector<Expr*> arguments): functionName(functionName), arguments(arguments){}
    any accept(Visitor* visitor) const override {return visitor->visitCallExpr(this);}
};

class Nil: public Expr{
public:
    Nil(){};
    any accept(Visitor* visitor) const override {return visitor->visitNilExpr(this);}       //fixme actually return nullptr?
};

class If: public Expr{
public:
    vector<Expr*> conditions;
    vector<Expr*> thenBranches;

    If(vector<Expr*> conditions, vector<Expr*> thenBranches): conditions(conditions), thenBranches(thenBranches) {}
    any accept(Visitor* visitor) const override {return visitor->visitIfExpr(this);}
};

class List: public Expr{
public:
    const Expr* car;
    const Expr* cdr;

    List(const Expr* car, const Expr* cdr): car(car), cdr(cdr){}
    any accept(Visitor* visitor) const override {return visitor->visitListExpr(this);}
};

class ListElement: public Expr{
public:
    const Token car_cdr;
    const Expr* list;
    ListElement(Expr* list, Token car_cdr): list(list), car_cdr(car_cdr){}
    any accept(Visitor* visitor) const override {return visitor->visitListElementExpr(this);}
};
#endif //LISP_EXPR_H
