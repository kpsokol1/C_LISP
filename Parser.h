#pragma once
#ifndef LISP_PARSER_H
#define LISP_PARSER_H

#include "TokenType.h"
#include "Stmt.h"
#include "ParseError.h"


class Parser{
private:
    const vector<Token> tokens;
    int current = 0; //points to the next token waiting to be parsed

    Expr* expression();

    Expr* equality();

    bool match(int num_args, ...);

    Token consume(TokenType type, string message);

    bool check(TokenType type);

    Token advance();

    bool isAtEnd();

    Token peek();

    Token previous();

    Expr* comparison();

    Expr* term();

    Expr* factor();

    Call* call();

    Expr* list();

    //parse argument list

    Expr* primary();

    void error(Token token, string message);
    ParseError parse_error(Token token, string message);

    void synchronize();
    void report(int line, string where, string message);

    Stmt* statement();

    Stmt* expressionStatement();

    Expr* ifStatement();

    Stmt* printStatement();

    Function* function();

    Stmt* varDeclaration();

    vector<Expr*> block();

    bool lookUpFunction(Token name);

    vector<string> functionNames;

    Expr* recursiveCdr();

public:
    Parser(const vector<Token> tokens);

    vector<Stmt*> parse();
};
#endif //LISP_PARSER_H
