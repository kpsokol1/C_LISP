cmake_minimum_required(VERSION 3.16)
project(lisp)

set(CMAKE_CXX_STANDARD 17)

add_executable(lisp Lisp.cpp Lisp.h Scanner.cpp Scanner.h global.cpp global.h Parser.cpp Parser.h Expr.h ParseError.h Stmt.h Interpreter.cpp Interpreter.h RuntimeError.h RuntimeError.cpp Environment.h Environment.cpp LispFunction.h LispFunction.cpp LispCallable.h _Return.h)