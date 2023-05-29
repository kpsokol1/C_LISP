#include "Lisp.h"
#include "global.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"

using namespace std;

int Lisp::main(int argc, char *argv[]) {
    hadError = false;
    if(argc > 2){
        cout << "Usage: jlox [script]" << endl;
        return 64;
    }
    else if(argc == 2){
        runFile(argv[1]);        //remember argv[0] is the name of the file
    }
    return 0;
}

void Lisp::runFile(string path){
    ifstream inputFile(path);
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string fileContents = buffer.str();
    run(fileContents);
    if(hadError) exit(65);
    if(hadRuntimeError) exit(70);           //don't care about runtime errors in REPL just continue on
}

void Lisp::run(string source){
    Scanner *scanner = new Scanner(source);
    vector<Token> tokens = scanner->scanTokens();
   //for(int i = 0; i < tokens.size(); i++){
   //     cout << tokens.at(i).to_string() << endl;
   //}

    if(hadError) return;
    Parser parser(tokens);
    vector<Stmt*> statements = parser.parse();

    //stop if there was a syntax error
    if(hadError) return;

    Interpreter* interpreter = new Interpreter;

    interpreter->interpret(statements);

}

int main(int argc, char *argv[]) {
    return Lisp::main(argc, argv);
}