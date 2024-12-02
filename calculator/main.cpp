#include <string>
#include <iostream>
#include "expression_evaluator.h"
using namespace std;
string expression;
evaluator ev;
int main() {
    cin >> expression;
    cout << ev.evaluate(expression);
    return 0;
}