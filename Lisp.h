#pragma once
#ifndef LISP_LISP_H
#define LISP_LISP_H

#include <string>
using namespace std;

class Lisp{
public:
    static int main(int argc, char *argv[]);

private:
    static void runFile(string path);

    static void run(string source);
};

#endif //LISP_LISP_H
