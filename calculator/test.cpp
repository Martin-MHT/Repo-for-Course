#include <iostream>
#include "expression_evaluator.h"
using namespace std;

int main() {
    // cout << ev.getNum("114514", 0) << endl;
    // cout << ev.getNum("1145.14", 0) << endl;
    // cout << ev.getNum("1.14514", 0) << endl;
    // cout << ev.getNum("11451e4", 0) << endl;
    // cout << ev.getNum("1145.1e4", 0) << endl;
    // cout << ev.getNum("114.14.1", 0) << endl;
    string Input;
    getline(cin, Input);
    cout << evaluator::evaluate(Input) << endl;
    // cout << ev.getNum("114e51e4", 0) << endl;
    // cout << ev.getNum("114e51.4", 0) << endl;
    // cout << ev.getNum("114514e", 0) << endl;
    // cout << ev.getNum("114514.", 0) << endl;
    // cout << ev.getNum("114514", 0) << endl;
    // cout << ev.getNum("11e4514", 0) << endl;
    // cout << ev.getNum("1145104", 0) << endl;
    // cout << ev.getNum("0114514", 0) << endl;
    return 0;
}