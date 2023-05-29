#include "Parser.h"
#include <string>
#include <stdarg.h>
#include <iostream>


Expr* Parser::expression(){
    return primary();
}

bool Parser::match(int num_args, ...) {
    va_list valist;
            va_start(valist,num_args);
    for (int i = 0; i < num_args; i++) {
        if (check(va_arg(valist,TokenType))) {
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::consume(TokenType type, string message){
    if(check(type)) return advance();
    throw parse_error(peek(),message);
}

bool Parser::check(TokenType type){
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance(){
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd(){
    return peek().type == TokenType::_EOF;
}

Token Parser::peek(){
    return tokens.at(current);
}

Token Parser::previous(){
    return tokens.at(current - 1);
}

Expr* Parser::primary(){
    if(match(1, TokenType::LEFT_PAREN)){
        if(match(8, TokenType::PLUS, TokenType::MINUS, TokenType::STAR, TokenType::SLASH, TokenType::LESS, TokenType::GREATER, TokenType::EQUAL, TokenType::EQ_Q)){
            Token _operator = previous();
            Expr* left = expression();
            Expr* right = expression();
            consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
            return new Binary(left, _operator, right);
        }
        if(match(5,TokenType::NUMBER_Q, TokenType::SYMBOL_Q, TokenType::LIST_Q, TokenType::NIL_Q, TokenType::PRINT)){
            Token _operator = previous();
            Expr* right = expression();
            consume(TokenType::RIGHT_PAREN, "Expect ')' after parameters.");
            return new Unary(_operator, right);
        }
        if(match(2,TokenType::AND_Q, TokenType::OR_Q)){
            Token _operator = previous();
            Expr* left = expression();
            Expr* right = expression();
            consume(TokenType::RIGHT_PAREN, "Expect ')' after parameters.");
            return new Logical(left, _operator, right);
        }
        if(match(1, TokenType::IDENTIFIER)){
            if(!lookUpFunction(previous())){
                throw parse_error(previous(), previous().lexeme + " is not a function name");
            }
            return call();
        }
        if(match(1, TokenType::CONS)){
            Expr* car = expression();
            Expr* cdr = expression();
            consume(TokenType::RIGHT_PAREN, "Expect ')' after parameters.");
            return new List(car, cdr);
        }
        if(match(2, TokenType::CAR, TokenType::CDR)){
            Token car_cdr = previous();
            Expr* list = expression();
            consume(TokenType::RIGHT_PAREN, "Expect ')' after parameters.");
            return new ListElement(list, car_cdr);       //fixme may want to pass it a list not just a expression
        }
        if(match(1, TokenType::COND)){
            return ifStatement();
        }
        if(match(1,TokenType::RIGHT_PAREN)){
            return new Nil();
        }
        throw parse_error(peek(),"Expect expression.");
    }

    if (match(1,TokenType::NUMBER)) {
        return new Number(previous().literal, previous().lexeme);
    }
    if(match(1, TokenType::TICK)) {
        if(check(TokenType::LEFT_PAREN)){
            Expr* _list = list();
            //consume(TokenType::RIGHT_PAREN, "Expect ')' after list.");
            return _list;
        }
        else if(match(1, TokenType::NUMBER)){
            return new Number(previous().literal,previous().lexeme);
        }
        else{
            advance();
            return new Symbol(previous().literal,previous().lexeme);            //fixme what is symbol has spaces in it
        }
    }
    if(match(1, TokenType::IDENTIFIER)){
        return new Variable(previous());
    }
    throw parse_error(peek(),"Expect expression.");
    return nullptr; //should be unreachable
}

void Parser::error(Token token, string message){
    if (token.type == TokenType::_EOF) {
        report(token.line, " at end", message);
    } else {
        report(token.line, " at '" + token.lexeme + "'", message);
    }
}

void Parser::report(int line, string where, string message){
    cerr << "[line " << to_string(line) <<"] Error" << where << ": " << message << endl;
    hadError = true;
}

ParseError Parser::parse_error(Token token, string message){
    error(token,message);
    return ParseError();
}

Parser::Parser(const vector<Token> tokens): tokens(tokens){}

Stmt* Parser::statement(){
    try{
        if(check(TokenType::LEFT_PAREN)) {
            consume(TokenType::LEFT_PAREN, "Expected opening '(' ");
            if (match(1, TokenType::DEFINE)) return function();
            if (match(1, TokenType::SET)) return varDeclaration();
            current--;      //fixme unconsume is this a problem? trying to make sure that the expression statement still gets the parentheses
        }
        return expressionStatement();
    }
    catch(ParseError parseError){
        synchronize();
        return nullptr;
    }
}

Stmt* Parser::expressionStatement(){
    Expr* expr = expression();
    return new Expression(expr);
}

Expr* Parser::ifStatement(){
    vector<Expr*> conditions;               //fixme do these need to be pointers?
    vector<Expr*> thenBranches;
    conditions.push_back(expression());
    thenBranches.push_back(expression());

    while(!check(TokenType::RIGHT_PAREN) && !isAtEnd()){
        conditions.push_back(expression());
        thenBranches.push_back(expression());
    }

    //closing of cond statement
    consume(TokenType::RIGHT_PAREN, "Expect ')' after parameters.");
    return new If(conditions, thenBranches);
}

Function* Parser::function(){        //kind is for identifying if in class or not
    Token name = consume(TokenType::IDENTIFIER, "Expect function name."); //parse function name
    functionNames.push_back(name.lexeme);
    consume(TokenType::LEFT_PAREN, "Expect '(' after function name.");
    vector<Token> parameters;
    if (!check(TokenType::RIGHT_PAREN)) {           //0 parameter case
        do {
            if (parameters.size() >= 255) {
                error(peek(), "Can't have more than 255 parameters.");
            }
            parameters.push_back(consume(TokenType::IDENTIFIER, "Expect parameter name."));
        } while (check(TokenType::IDENTIFIER));
    }
    consume(TokenType::RIGHT_PAREN, "Expect ')' after parameters.");

    vector<Expr*> body = block();
    return new Function(name, parameters, body);
}

vector<Expr*> Parser::block(){
    vector<Expr*> statements;

    while(!check(TokenType::RIGHT_PAREN) && !isAtEnd()){      //fixme is checking for right_paren right?                   //check for is at end because if forget the closing brace we don't want to be in an infinite loop
        statements.push_back(expression());
    }

    consume(TokenType::RIGHT_PAREN, "Expect ')' after block.");
    return statements;
}

//can't have list of mixed lists and atoms
Expr* Parser::list() {                                      //fixme do we handle nil lists correctly?
    Expr* car = new Nil();  //fixme nil or nullptr?
    Expr* cdr = new Nil(); //fixme nil or nullptr?

    if(match(1, TokenType:: NUMBER)){
        car =  new Number(previous().literal,previous().lexeme);
        if(!check(TokenType::RIGHT_PAREN)){
            if(check(TokenType::LEFT_PAREN)){
                throw parse_error(peek(), "Can't mix lists and non lists at same level");
            }
            cdr = list();
        }
        else{
            //consume(TokenType::RIGHT_PAREN, "Expect ')' after list.");
            cdr = new Nil();
        }

        return new List(car, cdr);
    }
    if(match(1, TokenType:: LEFT_PAREN)){
        if(!check(TokenType::RIGHT_PAREN)){
            if(!check(TokenType::LEFT_PAREN)){
                if(match(1, TokenType:: NUMBER)) {
                    car = new Number(previous().literal, previous().lexeme);
                }
                else if(match(1, TokenType::TICK)){
                    string test = previous().lexeme;
                    Expr* tick_car = new Symbol(previous().literal,previous().lexeme);
                    Expr* tick_cdr = list();
                    car = new List(tick_car,tick_cdr);
                }
                else{
                    advance();
                    car = new Symbol(previous().literal,previous().lexeme);
                }
            }
            else{
                car = list();
            }

            if(check(TokenType:: LEFT_PAREN ) || check(TokenType::TICK)){
                if((tokens.at(current+1).type == TokenType::RIGHT_PAREN)){  //at a nil
                    consume(TokenType::LEFT_PAREN, "Expected '( before a nil expression)");
                    consume(TokenType::RIGHT_PAREN, "Expected ') after a nil expression)");
                    Expr* right = list();
                    cdr = new List(new Nil(), right);
                }
                else{
                    cdr = recursiveCdr();
                }
            }  //|| (previous().type == TokenType::RIGHT_PAREN && !(check(TokenType::RIGHT_PAREN)))){
            else{
                if(previous().type == TokenType::RIGHT_PAREN){
                    throw parse_error(peek(), "Can't mix lists and non lists at same level");
                }
                cdr = list();
            }

        }
        else{
            car = new Nil();
            cdr = new Nil();
        }
        consume(TokenType::RIGHT_PAREN, "Expect ')' after list.");
        return new List(car, cdr);
    }
    if(check(TokenType::RIGHT_PAREN)){ //a cdr ran into this on a one element list
        return new Nil();
    }
    else{ //fixme is this right? can symbols inside of symbols inside of lists don't work so just make a literal?
        advance();
        car = new Symbol(previous().literal,previous().lexeme);
        if(!check(TokenType::RIGHT_PAREN)){
            cdr = list();
        }
        else{
            //consume(TokenType::RIGHT_PAREN, "Expect ')' after list.");
            cdr = new Nil();
        }
        return new List(car, cdr);
    }
}
Expr* Parser::recursiveCdr(){
    if(check(TokenType::RIGHT_PAREN)){
        return new Nil();
    }
    Expr* first = list();
    return new List(first, recursiveCdr());
}
Call* Parser::call(){
    Token functionName = previous();
    vector<Expr*> arguments;
    while(!check(TokenType::RIGHT_PAREN) || isAtEnd()){
        arguments.push_back(expression());
    }

    Token paren = consume(TokenType::RIGHT_PAREN,"Expect ')' after arguments.");
    return new Call(functionName,arguments);
}

Stmt* Parser::varDeclaration(){     //fixme do we need to check if we are at the global level or not?
    Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");

    Expr* initializer = expression();       //fixme could be nullptr

    consume(TokenType::RIGHT_PAREN, "Expect ')' after variable declaration.");
    return new Var(name, initializer);
}

Stmt* Parser::printStatement(){
    Expr* value = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after print statement.");
    return new Print(value);
}

bool Parser::lookUpFunction(Token name){
    for(int i = 0; i < functionNames.size(); i++){
        if(functionNames.at(i) == name.lexeme) return true;
    }
    return false;
}

vector<Stmt*> Parser::parse(){
    vector<Stmt*> statements;
    while(!isAtEnd()){
            statements.push_back(statement());

    }
    return statements;
}

void Parser::synchronize(){
    while (!isAtEnd()) {
        if (previous().type == TokenType::SEMICOLON) return;
        if(peek().type == TokenType::LEFT_PAREN){
            advance();
            if(peek().type == TokenType::SET || peek().type == TokenType::DEFINE){
                current--;  //go back to open paren
                return;
            }
        }
        advance();
    }
}

