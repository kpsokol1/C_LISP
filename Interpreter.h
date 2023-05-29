#pragma once
#ifndef LISP_INTERPRETER_H
#define LISP_INTERPRETER_H
#include "Stmt.h"
#include "Environment.h"
#include "RuntimeError.h"
using namespace std;

class Interpreter: public Visitor, public Stmt_visitor{
public:
    Interpreter();
    ~Interpreter();
    Environment* globals = new Environment;
    void interpret (vector<Stmt*> statements);
    any visitLiteralExpr(const Literal* expr);

    any visitNumberExpr(const Number* expr);

    any visitSymbolExpr(const Symbol* expr);

    any visitNilExpr(const Nil* expr);

    any visitUnaryExpr(const Unary* expr);

    any visitVariableExpr(const Variable* expr);

    void visitExpressionStmt(const Expression* stmt);

    void visitPrintStmt(const Print* stmt);

    any visitBinaryExpr(const Binary* expr);

    void visitVarStmt(const Var* stmt);

    any visitListExpr(const List* stmt);

    any visitListElementExpr(const ListElement* stmt);

    any evaluateListElement(const List* list, bool isCar);

    string printList(const Expr* list);

    any visitIfExpr(const If* expr);

    any visitCallExpr(const Call* expr);

    any visitLogicalExpr(const Logical* expr);

    void visitFunctionStmt(const Function* stmt);

    void executeBlock(vector<Expr*> statements, Environment* environment);

private:
    Environment* environment = globals;
    unordered_map<const Expr*, int>* locals = new unordered_map<const Expr*,int>; //fixme does this work?
    any evaluate(const Expr* expr);

    void execute(const Stmt* stmt);

    bool isTruthy (any object);

private:

    bool isEqual(any a, any b);
    any lookUpVariable(Token name, const Expr* expr, Environment* environment);

    void checkNumberOperands(Token _operator, any left, any right);
    string stringify(any object);

    void runtimeError(RuntimeError error);
};
#endif //LISP_INTERPRETER_H
