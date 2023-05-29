#include <string>
#include "Interpreter.h"
#include "_Return.h"
#include "LispFunction.h"
#include <algorithm>
#include <sstream>

using namespace std;

Interpreter::Interpreter()= default;
Interpreter::~Interpreter()= default;
void Interpreter::interpret (vector<Stmt*> statements){
    try{
        vector<Stmt*>::iterator it;

        for(it = statements.begin(); it != statements.end(); it++) {
            execute((*it));
            //we want to print every expressionStatement
        }
    }
    catch (RuntimeError error) {
        runtimeError(error);
    }
}
any Interpreter::visitLiteralExpr(const Literal* expr){
    return expr->value;
}

any Interpreter::visitNumberExpr(const Number* expr){
    return expr->value;
}

any Interpreter::visitSymbolExpr(const Symbol* expr){
    string value = expr->stringValue;
    return expr->stringValue;
}

any Interpreter::visitNilExpr(const Nil *expr) {
    return nullptr;
}

any Interpreter::visitUnaryExpr(const Unary* expr){
    any right = evaluate(expr->right);          //recursive part (post order traversal)

    switch(expr->_operator.type){
        case TokenType::NUMBER_Q:{
            return (right.type() == typeid(double)); //fixme does this need to be T?
        }


        case TokenType::SYMBOL_Q:
            return right.type() == typeid(string);
        case TokenType::LIST_Q:
            return right.type() == (typeid(const List*));
        case TokenType::NIL_Q:
            if(isTruthy(right)){
                return false;
            }
            return true;

        case TokenType::PRINT:
            cout << stringify(right) << endl;
            return nullptr;
    }

    //unreachable
    return nullptr;
}

any Interpreter::visitVariableExpr(const Variable* expr){
    //return environment->get(expr->name);
    return lookUpVariable(expr->name,expr, environment);
}

void Interpreter::visitExpressionStmt(const Expression* stmt){
    cout << stringify(evaluate(stmt->expression)) << endl;
}

void Interpreter::visitPrintStmt(const Print* stmt){
    any value = evaluate(stmt->expression);
    cout << stringify(value) << endl;
}

any Interpreter::visitBinaryExpr(const Binary* expr){       //fixme do we need to change check for a double to checking for an int? and does it need to be integer instead of int?
    any left = evaluate(expr->left);
    any right = evaluate(expr->right);
    TokenType type = expr->_operator.type;
    switch (type) {
        case TokenType::EQUAL:
            if((left.type() != typeid(double) && left.type() != typeid(string) && left.type() != typeid(nullptr)) || (right.type() != typeid(double) && right.type() != typeid(string) && right.type() != typeid(nullptr))){
                return nullptr;
            }
            if(left.type() != right.type()){
                return nullptr;
            }
            if(left.type() == typeid(string)){
                return any_cast<string>(left) == any_cast<string>(right);
            }
            if(left.type() == typeid(nullptr)){
                return true;
            }
            return any_cast<double>(left) == any_cast<double>(right);
        case TokenType::EQ_Q:
            if((left.type() != typeid(double) && left.type() != typeid(string) && left.type() != typeid(nullptr)) || (right.type() != typeid(double) && right.type() != typeid(string) && right.type() != typeid(nullptr))){
                return nullptr;
            }
            if(left.type() != right.type()){
                return nullptr;
            }
            if(left.type() == typeid(string)){
                return any_cast<string>(left) == any_cast<string>(right);
            }
            if(left.type() == typeid(nullptr)){
                return true;
            }
            return any_cast<double>(left) == any_cast<double>(right);
        case TokenType::GREATER:
            checkNumberOperands(expr->_operator,left,right);     //throws exception so no need for if statement here
            return any_cast<double>(left) > any_cast<double>(right);
        case TokenType::LESS:
            checkNumberOperands(expr->_operator,left,right);
            return any_cast<double>(left) < any_cast<double>(right);
        case TokenType::MINUS:
            checkNumberOperands(expr->_operator,left,right);
            return any_cast<double>(left) - any_cast<double>(right);
        case TokenType::PLUS:
            checkNumberOperands(expr->_operator,left,right);
            return any_cast<double>(left) + any_cast<double>(right);
        case TokenType::SLASH:{
            checkNumberOperands(expr->_operator,left,right);
            int denominator = (int)any_cast<double>(right);
            if(denominator == 0){
                throw RuntimeError(expr->_operator, "Attempted to divide by 0");
            }
            return (double)((int)any_cast<double>(left) / (int)any_cast<double>(right));
        }

        case TokenType::STAR:
            checkNumberOperands(expr->_operator,left,right);
            return any_cast<double>(left) * any_cast<double>(right);
    }
    // Unreachable.
    return nullptr;
}

void Interpreter::visitVarStmt(const Var* stmt){
    any value = nullptr;
    if(stmt->initializer != nullptr){                        //check to see if we intialized the declared variable
        value = evaluate(stmt->initializer);                //fixme is this right?
    }
    environment->define(stmt->name.lexeme, value);      //fixme why do we have duplicate
}

any Interpreter::visitListExpr(const List* expr){
    const Expr* car_exp = expr->car;
    const Expr* cdr_exp = expr->cdr;

    any car = evaluate(expr->car);
    if(car.type() == typeid(const List*)){  //we just came from a variable and we acutally need to visit the list
        car = evaluate(any_cast<const List*>(car));
    }
    any cdr = evaluate(expr->cdr);
    if(cdr.type() == typeid(const List*)){  //we just came from a variable and we acutally need to visit the list
        cdr = evaluate(any_cast<const List*>(cdr));
    }
    if(car.type() == typeid(double)){                                               //fixme do we need to worry about any other types?
        car_exp = new Number(car, to_string(any_cast<double>(car)));
    }
    else if(car.type() == typeid(string)){
        car_exp = new Symbol(car, any_cast<string>(car));
    }
    else if(car.type() == typeid(nullptr)){
        car_exp = new Nil();
    }
    else{
        car_exp = any_cast<const List*>(car);
    }
    //else{
    //    car_exp = any_cast<Expr*>(evaluate(any_cast<const List*>(car)));
    //}

    if(cdr.type() == typeid(double)){
        cdr_exp = new Number(cdr, to_string(any_cast<double>(cdr)));
    }
    else if(cdr.type() == typeid(string)){
        cdr_exp = new Symbol(cdr, any_cast<string>(cdr));
    }
    else if(cdr.type() == typeid(nullptr)){
        cdr_exp = new Nil();
    }
    else{
        cdr_exp = any_cast<const List*>(cdr);
    }
    //else{
      //  cdr_exp = any_cast<Expr*>(evaluate(any_cast<const List*>(cdr)));
    //}
    return new const List(car_exp, cdr_exp);    //fixme will this work if car is just a number?
    //return expr; //for isTruthy reasons
}

any Interpreter::visitListElementExpr(const ListElement *expr) {            //fixme do wee need to evaluate for list element too?
    if(expr->car_cdr.type == TokenType::CAR){
       any value = evaluate(expr->list);
        if(value.type() == typeid(const List*)){
            const List* list = any_cast<const List*>(value);
            any value2 = evaluate(list->car);
            if(value2.type() == typeid(nullptr)){
                return nullptr;
            }
            if(value2.type() == typeid(double)){                //fixme what about symbols bools and other types
                return any_cast<double>(value2);
            }
            return value2;
        }
   }
    if(expr->car_cdr.type == TokenType::CDR){
        any value = evaluate(expr->list);
        if(value.type() == typeid(const List*)){
            const List* list = any_cast<const List*>(value);
            any value2 = evaluate(list->cdr);
            if(value2.type() == typeid(nullptr)){
                return nullptr;
            }
            if(value2.type() == typeid(double)){
                return any_cast<double>(value2);
            }
            return value2;
        }
    }
    throw RuntimeError(expr->car_cdr,"Invalid access on list");
    return nullptr; //should be unreachable
}

void Interpreter::visitFunctionStmt(const Function *stmt) {         //for function declarations the isInitializer is always false
    LispFunction* function = new LispFunction(stmt, environment);
    environment->define(stmt->name.lexeme, function);
}

any Interpreter::visitCallExpr(const Call* expr){
    Token callee = expr->functionName;

    vector<any> arguments;

    vector<Expr*>::const_iterator it;

    for(it = expr->arguments.begin(); it != expr->arguments.end(); it++){
        arguments.push_back(evaluate((*it)));
    }

    if (environment->get(callee).type() == typeid(LispFunction*)){
        LispFunction* function = any_cast<LispFunction*>(environment->get(callee));         //all Lox functions have to implement this interface

        if (arguments.size() != function->arity()) {         //checking arity (the right number of arguments were passed)
            throw RuntimeError(callee, "Expected " + to_string(function->arity()) + " arguments but got " + to_string(arguments.size()) + ".");
        }
        return function->call(this, arguments);
    }
    else{
        throw RuntimeError(callee,"Can only call functions and classes.");
    }
}

any Interpreter::visitIfExpr(const If* stmt){
    for(int i = 0; i < stmt->conditions.size(); i++){                 //fixme can we ensure conditions and statements are the same?
        if (isTruthy(evaluate(stmt->conditions.at(i)))) {       //fixme what if there are no true if conditions?
            any value = (evaluate(stmt->thenBranches.at(i)));
            //evaluate(any_cast<const List*>(value));
            //throw _Return(value);
            return value;
        }
    }
    string hello;

    //throw RuntimeError(,"No conditions evaluated to True");
    return nullptr; //should be unreachable
}

any Interpreter::visitLogicalExpr(const Logical* expr){
    any left = evaluate(expr->left);

    if (expr->_operator.type == TokenType::OR_Q) {
        if (isTruthy(left)) return true;
    }
    else {
        if (!isTruthy(left)) return false;
    }

    return isTruthy(evaluate(expr->right));               //don't explicitly return true or false, just return a truthy or falsey element
}

void Interpreter::executeBlock(vector<Expr*> statements, Environment* environment){
    Environment* previous = this->environment;
    try{
        this->environment = environment;
        any value;
        for(int i = 0; i < statements.size(); i++){
            if(i == statements.size()-1){
                value = (evaluate(statements.at(i)));
                throw _Return(value);    //double throw on a cond? //return last value in function?
            }
            evaluate((statements.at(i)));
        }
    }catch(...){
        this->environment = previous;
        throw;
    }

    this->environment = previous;
}

any Interpreter::evaluate(const Expr* expr){
    return expr->accept(this);
}

void Interpreter::execute(const Stmt* stmt){
    stmt->accept(this);
}

bool Interpreter::isTruthy (any object){
    if(object.type() == typeid(double)) return true;
    if(object.type() == typeid(bool)) return any_cast<bool>(object);
    if(object.type() == typeid(nullptr)) return false;
    //if(evaluate(any_cast<Expr*>(object)).type() == typeid(nullptr)) return false;
    return true;    //fixme should this ever have a fall through case?
}

void Interpreter::checkNumberOperands(Token _operator, any left, any right) {
    if (left.type() == typeid(double) && right.type() == typeid(double)) return;
    throw RuntimeError(_operator, "Operands must be numbers.");
}

string Interpreter::stringify(any object) {
    if(object.type() == typeid(bool)){
        if(any_cast<bool>(object)){
            return "T";
        }
        return "()";
    }
    if (object.type() == typeid(nullptr)) return "()";

    if (object.type() == typeid(double)) {
        int doubleVersion = (int)any_cast<double>(object);
        return to_string(doubleVersion);
    }
    if(object.type() == typeid(int)){
        int intVersion = any_cast<int>(object);
        return to_string(intVersion);
    }

    //print list?
    if(object.type() == typeid(const List*)){
        string returnString = "( " + printList(any_cast<const List*>(object)) +")\n";
        if(returnString.size() >=3){
            if(returnString.substr(returnString.size() - 4) == "()) ") {                        //fixme do we need to check if string is less than 3?
                returnString = returnString.substr(0, returnString.size() - 4);
            }
        }
        return returnString;
    }

    //assuming we are at a string
    string returnString = any_cast<string>(object);
    transform(returnString.begin(), returnString.end(),returnString.begin(), ::toupper);
    return returnString;       //fixme we shouldn't even get here right?
}

string Interpreter::printList(const Expr* list){
    stringstream outputstream;
    string temp = outputstream.str();
    any evalList = evaluate(list);
    if(evalList.type() == typeid(const List*)){
        if (evaluate(any_cast<const List*>(evalList)->car).type() == typeid(const List*)) {
            outputstream << "( " <<printList(any_cast<const List *>(evalList)->car) << ") ";
            string temp2 = outputstream.str();
                outputstream << printList(any_cast<const List *>(evalList)->cdr);
        }
        else{
            outputstream << stringify(evaluate(any_cast<const List*>(evalList)->car)) << " ";
            outputstream << printList(any_cast<const List *>(evalList)->cdr);
        }
    }
    else if(evalList.type() == typeid(double) || evalList.type() == typeid(string)){    //dotted lists
        outputstream << ". " << stringify(evalList) << " ";
    }
    //else{
     //   outputstream << stringify(evalList);
    //}

    return outputstream.str();
}

void Interpreter::runtimeError(RuntimeError error){
    cerr << error.message << "\n" << "[line " << error.token.line << "]" << endl;       //fixme cerr doesn't always print out?
    hadRuntimeError = true;
}


any Interpreter::lookUpVariable(Token name, const Expr* expr, Environment* environment){
    if (environment->values.find(name.lexeme) != environment->values.end()){
        return environment->get(name);  //we know the
    }
    else {
        return globals->get(name);
    }
}