#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
void Test6();
void Test7();
void Test8();
void Test9();
void Test10();
void Test11();
void Test12();
void Test13();
void compareFiles(string resultsFile, string correctFile, int testNumber);

int main(){
    cout << "Begin Testing: "<< endl;
    system("g++ Lisp.cpp Scanner.cpp global.cpp Parser.cpp Interpreter.cpp RuntimeError.cpp Environment.cpp LispFunction.cpp -std=c++17");
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    Test10();
    Test11();
    Test12();
    Test13();
    cout << "Testing Finished" << endl;
    return 0;
}
void compareFiles(string resultsFile, string correctFile, string testname){
    ifstream results(resultsFile);
    ifstream correct(correctFile);

    string resultLine;
    string correctLine;
    int lineNumber = 1;
    while(!results.eof() || !correct.eof()) {
        getline(results, resultLine);
        getline(correct, correctFile);
        if (resultLine != correctFile) {
            cout << "Test: (" << testname << ") failed at line: " << to_string(lineNumber) << endl;
            return;
        }
        lineNumber++;
    }
    cout << "Test: (" << testname << ") : pass" << endl;
}

void Test1(){
    system("./a.out test_inputs/comparison.lisp > test_results/comparison_results.txt 2>&1");
    compareFiles("test_results/comparison_results.txt", "test_expected_output/comparison_correct.txt","comparison");
}

void Test2(){
    system("./a.out test_inputs/cond_test.lisp > test_results/cond_test_results.txt 2>&1");
    compareFiles("test_results/cond_test_results.txt", "test_expected_output/cond_test_correct.txt","cond_test");
}

void Test3(){
    system("./a.out test_inputs/empty_list_error.lisp > test_results/empty_list_error_results.txt 2>&1");
    compareFiles("test_results/empty_list_error_results.txt", "test_expected_output/empty_list_error_correct.txt","empty_list_error");
}

void Test4(){
    system("./a.out test_inputs/function_tests.lisp > test_results/function_tests_results.txt 2>&1");
    compareFiles("test_results/function_tests_results.txt", "test_expected_output/function_tests_correct.txt","function_tests");
}

void Test5(){
    system("./a.out test_inputs/list_ops.lisp > test_results/list_ops_results.txt 2>&1");
    compareFiles("test_results/list_ops_results.txt", "test_expected_output/list_ops_correct.txt","list_ops");
}

void Test6(){
    system("./a.out test_inputs/logical.lisp > test_results/logical_results.txt 2>&1");
    compareFiles("test_results/logical_results.txt", "test_expected_output/logical_correct.txt","logical");
}

void Test7(){
    system("./a.out test_inputs/number_operands_error.lisp > test_results/number_operands_error_results.txt 2>&1");
    compareFiles("test_results/number_operands_error_results.txt", "test_expected_output/number_operands_error_correct.txt","number_operands_error");
}

void Test8(){
    system("./a.out test_inputs/parsing_errors_1.lisp > test_results/parsing_errors_1_results.txt 2>&1");
    compareFiles("test_results/parsing_errors_1_results.txt", "test_expected_output/parsing_errors_1_correct.txt","parsing_errors_1");
}

void Test9(){
    system("./a.out test_inputs/parsing_errors_2.lisp > test_results/parsing_errors_2_results.txt 2>&1");
    compareFiles("test_results/parsing_errors_2_results.txt", "test_expected_output/parsing_errors_2_correct.txt","parsing_errors_2");
}

void Test10(){
    system("./a.out test_inputs/parsing_errors_3.lisp > test_results/parsing_errors_3_results.txt 2>&1");
    compareFiles("test_results/parsing_errors_3_results.txt", "test_expected_output/parsing_errors_3_correct.txt","parsing_errors_3");
}

void Test11(){
    system("./a.out test_inputs/plus.lisp > test_results/plus_results.txt 2>&1");
    compareFiles("test_results/plus_results.txt", "test_expected_output/plus_correct.txt","plus");
}

void Test12(){
    system("./a.out test_inputs/questions.lisp > test_results/questions_results.txt 2>&1");
    compareFiles("test_results/questions_results.txt", "test_expected_output/questions_correct.txt","questions");
}

void Test13(){
    system("./a.out test_inputs/insertion_sort.lisp > test_results/insertion_sort_results.txt 2>&1");
    compareFiles("test_results/insertion_sort_results.txt", "test_expected_output/insertion_sort_correct.txt","insertion_sort");
}


