#ifndef LISP_TOKENTYPE_H
#define LISP_TOKENTYPE_H
#include <unordered_map>
#include "global.h"
using namespace std;
enum class TokenType{
    LEFT_PAREN, RIGHT_PAREN,
    MINUS, PLUS, SLASH, STAR, TICK, SEMICOLON, //fixme do we need the tick? whatabout on T

    EQUAL,GREATER,LESS,

    IDENTIFIER, NUMBER,T,NIL,

    DEFINE,SET,CONS,COND,CAR,CDR,AND_Q,OR_Q,NUMBER_Q,SYMBOL_Q,LIST_Q,NIL_Q,EQ_Q,PRINT,

    _EOF
};


typedef struct{
    const TokenType type;
    const string lexeme;
    const any literal;
    const int line;
    string to_string(){
        unordered_map<TokenType, string> token_names;
        token_names[TokenType::LEFT_PAREN] = "LEFT_PAREN";
        token_names[TokenType::RIGHT_PAREN] = "RIGHT_PAREN";
        token_names[TokenType::MINUS] = "MINUS";
        token_names[TokenType::PLUS] = "PLUS";
        token_names[TokenType::SLASH] = "SLASH";
        token_names[TokenType::STAR] = "STAR";
        token_names[TokenType::SEMICOLON] = "SEMICOLON";
        token_names[TokenType::EQUAL] = "EQUAL";
        token_names[TokenType::GREATER] = "GREATER";
        token_names[TokenType::LESS] = "LESS";
        token_names[TokenType::IDENTIFIER] = "IDENTIFIER";
        token_names[TokenType::NUMBER] = "NUMBER";
        token_names[TokenType::AND_Q] = "AND?";
        token_names[TokenType::COND] = "COND";
        token_names[TokenType::CONS] = "CONS";
        token_names[TokenType::CAR] = "CAR";
        token_names[TokenType::CDR] = "CDR";
        token_names[TokenType::NUMBER_Q] = "NUMBER?";
        token_names[TokenType::SYMBOL_Q] = "SYMBOL?";
        token_names[TokenType::LIST_Q] = "LIST?";
        token_names[TokenType::NIL_Q] = "NIL?";
        token_names[TokenType::NIL] = "NIL";
        token_names[TokenType::EQ_Q] = "EQ?";
        token_names[TokenType::T] = "T";
        token_names[TokenType::DEFINE] = "DEFINE";
        token_names[TokenType::OR_Q] = "OR?";
        token_names[TokenType::TICK] = "TICK";
        token_names[TokenType::T] = "T";
        token_names[TokenType::SET] = "SET";
        token_names[TokenType::_EOF] = "EOF";
        token_names[TokenType::PRINT] = "PRINT";

        return token_names[type] + " " + lexeme;
    }
} Token;

#endif //LISP_TOKENTYPE_H
