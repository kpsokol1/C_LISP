#include "LispFunction.h"
#include "Interpreter.h"
#include "_Return.h"

LispFunction::LispFunction(const Function* declaration, Environment* closure): declaration(declaration), closure(closure){}

any LispFunction::call(Interpreter* interpreter, vector<any> arguments){
    Environment* environment = new Environment(closure);

    vector<Token>::const_iterator it;

    for (int i = 0; i < declaration->params.size(); i++) {                                  //safe to assume params.size() and arguments.size() are the same because visitCallExpr checks beforehand
        environment->define(declaration->params.at(i).lexeme,arguments.at(i));
    }
    try{
        interpreter->executeBlock(declaration->body, environment);
    }
    catch(_Return returnValue){
        return returnValue.value;
    }

    return nullptr; //returns nil back to the caller
}

int LispFunction::arity(){
    return declaration->params.size();
}

string LispFunction::toString(){
    return "<fn " + declaration->name.lexeme + ">";
}

