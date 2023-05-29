#include <unordered_map>
#include "Environment.h"
#include "RuntimeError.h"

using namespace std;
Environment::Environment(){
    enclosing = nullptr;                        //global scope
}

Environment::Environment(Environment* enclosing){
    this->enclosing = enclosing;
}
void Environment::define(const string name, const any value) {
    values[name] = value;
}

any Environment::get(Token name) {
    if(values.find(name.lexeme) != values.end()){
        return values.at(name.lexeme);
    }

    if(enclosing != nullptr) return enclosing->get(name);   //recursive

    throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}

Environment* Environment::ancestor(int distance){
    Environment* environment = this;
    for (int i = 0; i < distance; i++) {
        environment = environment->enclosing;
    }
    return environment;
}

void Environment::assign(Token name, any value){
   if(values.find(name.lexeme) != values.end()) {
       define(name.lexeme,value);
       return;
   }

   if(enclosing != nullptr){
       enclosing->assign(name,value);
       return;
   }

   throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}

