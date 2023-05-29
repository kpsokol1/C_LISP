#pragma once
#ifndef LISP_STMT_H
#define LISP_STMT_H
#include "Expr.h"

class Expression;
class Print;
class Var;
class Function;

class Stmt_visitor{
public:
    virtual void visitExpressionStmt(const Expression* stmt) = 0;
    virtual void visitVarStmt(const Var* stmt) = 0;
    virtual void visitPrintStmt(const Print* stmt) = 0;
    virtual void visitFunctionStmt(const Function* stmt) = 0;
};
class Stmt{
public:
    virtual void accept(Stmt_visitor* stmt_visitor) const = 0;
};

class Expression: public Stmt{
public:
    const Expr* expression;
    Expression(Expr* expression): expression(expression){}
    void accept(Stmt_visitor* stmt_visitor) const override {stmt_visitor->visitExpressionStmt(this);}
};

class Function: public Stmt{
public:
    const Token name;
    vector<Token> params;   //parameters
    vector<Expr*> body; //why can't this be a block?
    Function(Token name, vector<Token> params, vector<Expr*> body):name(name), params(params), body(body){}
    void accept(Stmt_visitor* stmt_visitor) const override {stmt_visitor->visitFunctionStmt(this);}
};

class Print: public Stmt{
public:
    const Expr* expression;
    Print(Expr* expression): expression(expression){}
    void accept(Stmt_visitor* stmt_visitor) const override {stmt_visitor->visitPrintStmt(this);}
};

class Var: public Stmt{
public:
    const Token name;
    const Expr* initializer;
    Var(Token name, Expr* initializer): name(name), initializer(initializer){}
    void accept(Stmt_visitor* stmt_visitor) const override {stmt_visitor->visitVarStmt(this);}
};
#endif