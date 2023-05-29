#pragma once
#ifndef LISP_SCANNER_H
#define LISP_SCANNER_H
#include <string>
#include <vector>
#include "TokenType.h"

using namespace std;
class Scanner{
public:
    Scanner(string source);
    vector<Token> scanTokens();
    unordered_map<string, TokenType> create_keyword_map(){
        unordered_map<string, TokenType> map;
        map["define"] = TokenType::DEFINE;
        map["set"] =  TokenType::SET;
        map["cons"] =   TokenType::CONS;
        map["cond"] =  TokenType::COND;
        map["car"] =    TokenType::CAR;
        map["cdr"] =    TokenType::CDR;
        map["and?"] =     TokenType::AND_Q;
        map["or?"] =    TokenType::OR_Q;
        map["number?"] = TokenType::NUMBER_Q;
        map["symbol?"] =  TokenType::SYMBOL_Q;
        map["list?"] = TokenType::LIST_Q;
        map["nil?"] =  TokenType::NIL_Q;
        map["eq?"] =   TokenType::EQ_Q;
        map["print"] = TokenType::PRINT;
        return map;
    }
    unordered_map<string, TokenType> keywords = create_keyword_map();

private:
    const string source;
    vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

    bool isAtEnd();

    void scanToken();

    char advance();

    void addToken(TokenType type, string lexeme);
    void addToken(TokenType type, string text, any literal);

    Token createToken(TokenType type, string lexeme, any literal, int line);

    char peek();

    bool isDigit(char c);

    void number();

    void identifier();

    bool isAlpha(char c);

    bool isAlphaNumeric(char c);

    void error(int line, string message);

    void report(int line, string where, string message);
};
#endif //LISP_SCANNER_H
