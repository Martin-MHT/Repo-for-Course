#include <string>
#include <iostream>
#include "expression_evaluator.h"
using namespace std;
string expression;
int main() {
    evaluator ev;
    getline(cin, expression);
    cout << ev.evaluate(expression) << endl;
    return 0;
}