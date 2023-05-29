#include "Scanner.h"
#include <string>
#include <algorithm>
using namespace std;
Scanner::Scanner(string source): source(source){}
vector<Token> Scanner::scanTokens(){
    while(!isAtEnd()){
        //We are at the beginning of the next lexeme
        start = current;
        scanToken();
    }
    Token token = createToken(TokenType::_EOF,"", nullptr,line);
    tokens.push_back(token);
    return tokens;
}

bool Scanner::isAtEnd(){
    return current >= source.length();
}

void Scanner::scanToken(){
    char c = advance();
    switch(c){
        //one token identifiers
        case '(': addToken(TokenType::LEFT_PAREN, "("); break;
        case ')': addToken(TokenType::RIGHT_PAREN, ")"); break;
        case '-': addToken(TokenType::MINUS, "-"); break;
        case '+': addToken(TokenType::PLUS, "+"); break;
        case '*': addToken(TokenType::STAR, "*"); break;
        case '/': addToken(TokenType::SLASH, "/"); break;
        case '\'':
            addToken(TokenType::TICK, "\'"); break;
        case ';':
            while (peek() != '\n' && !isAtEnd()){
                advance();
            }  break;  //only allowing 1 line comments?
        case '=': addToken(TokenType::EQUAL, "="); break;
        case '<': addToken(TokenType::LESS, "<"); break;
        case '>': addToken(TokenType::GREATER, ">"); break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;

        case '\n':
            line++;
            break;

            //literals
        default:
            if (isDigit(c)) {
                number();
            }
            else if (isAlpha(c)){
                identifier();
            }
            else {
                error(line, "Unexpected character.");
            }
            break;
    }
}
char Scanner::advance(){
    return source.at(current++);
}

void Scanner::addToken(TokenType type, string lexeme){
    addToken(type, lexeme, nullptr);
}
void Scanner::addToken(TokenType type, string text, any literal){
    tokens.push_back(createToken(type,text,literal,line));
}

Token Scanner::createToken(TokenType type, string lexeme, any literal, int line){
    Token token = {type, lexeme,literal,line};
    return token;
}

char Scanner::peek(){
    if(isAtEnd()) return '\0';
    return source.at(current);
}

bool Scanner::isDigit(char c){
    return c >= '0' && c <= '9';
}

void Scanner::number(){
    while(isDigit(peek())) advance();
    addToken(TokenType::NUMBER,source.substr(start, current-start),stod(source.substr(start, current-start)));
}

void Scanner::identifier(){
    while (isAlphaNumeric(peek())) advance();

    string text = source.substr(start,current-start);
    TokenType type;

    //no type found
    string lowercase_text = text;
    // convert string to back to lower case
   transform(lowercase_text.begin(),lowercase_text.end(),lowercase_text.begin(),::tolower);
    if(keywords.find(lowercase_text) == keywords.end()){
        type = TokenType::IDENTIFIER;
    }
    else{
        type = keywords[lowercase_text];
    }
    addToken(type,text,nullptr);
}

bool Scanner::isAlpha(char c){
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_' || c== '?' || c== '!';      //fixme add valid characters to token
}

bool Scanner::isAlphaNumeric(char c){
    return isAlpha(c) || isDigit(c);
}

void Scanner::error(int line, string message){
    report(line, "", message);
}

void Scanner::report(int line, string where, string message){
    cerr << "[line " << to_string(line) <<"] Error" << where << ": " << message << endl;
    hadError = true;
}
