#ifndef EXPRESSION_EVALUATOR
#define EXPRESSION_EVALUATOR
#include <stack>
#include <string>
#include <cctype>
#include <cassert>
#include "calcexceptions.h"
using namespace std;

constexpr double EPS = 1e-18;

class evaluator {
    private :

    static bool delim(char ch) { return ch == ' '; }

    static bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/';
    }
    static bool isBracket(char ch) {
        return ch == '(' || ch == ')';
    }
    static bool isUnary(char ch) {
        return ch == '+' || ch == '-';
    }
    static bool isValid(char ch) {
        return delim(ch) || isdigit(ch) || isOperator(ch) || isBracket(ch) || ch == 'e' || ch == '.';
    }
    static double abs(double num) {
        return num < 0 ? -num : num;
    }
    static bool isZero(double num) {
        return abs(num) <= EPS;
    }

    static int opPriority(char op) {
        if(op < 0)  return 3;
        else if(op == '-' || op == '+') return 1;
        else if(op == '*' || op == '/') return 2;
        else return -1;
    }

    protected :
    static double getNum(const string& expression, size_t &pos) {
        if(expression[pos] == 'e' || expression[pos] == '.')
            throw invalidInputNumberException {};
        double ret = expression[pos] - '0';
        while(pos + 1 < expression.size() && isdigit(expression[pos + 1]))
            ++pos, ret = ret * 10 + (expression[pos] - '0');

        if(pos + 1 < expression.size() && expression[pos + 1] == '.') {
            ++pos;
            if(pos + 1 == expression.size() || !isdigit(expression[pos + 1]))
                throw invalidInputNumberException {};
            for(double eps = 1.0;
                pos + 1 < expression.size() && isdigit(expression[pos + 1]);
                eps *= 0.1, ret += eps * (expression[++pos] - '0'));
        }
        if(pos + 1 < expression.size() && expression[pos + 1] == 'e') {
            ++pos;
            if(pos + 1 == expression.size() || (!isdigit(expression[pos + 1]) && expression[pos + 1] != '-'))
                throw invalidInputNumberException {};
            bool negative = false;
            int exp = 0;
            if(expression[pos + 1] == '-')
                ++pos, negative = true;
            for(; pos + 1 < expression.size() && isdigit(expression[pos + 1]);
                  exp = exp * 10 + (expression[++pos] - '0'));
            // cout << "TEST: exp = " << exp << endl;
            if(pos + 1 < expression.size() && (expression[pos + 1] == '.' || expression[pos + 1] == 'e'))
                throw invalidInputNumberException {};
            for(double temp = 10.0; exp; exp >>= 1, temp = temp * temp)
               if(exp & 1) negative ? (ret /= temp) : (ret *= temp);
        }
        if(pos + 1 < expression.size() && (expression[pos + 1] == 'e' || expression[pos + 1] == '.'))
            throw invalidInputNumberException {};
        return ret;
    }

    static void calcWithOperator(stack<double>& st, char op) {
        if(isBracket(op))
            throw bracketMismatchException {};
        if(st.empty())
            throw operatorMismatchException {};
        if(op < 0) {
            double num = st.top();
            st.pop();
            if(-op == '-')  st.emplace(-num);
            else st.emplace(num);
        } else {
            double l, r;
            r = st.top(); st.pop();
            if(st.empty())
                throw operatorMismatchException {};
            l = st.top(); st.pop();
            if(op == '+')
                st.emplace(l + r);
            else if(op == '-')
                st.emplace(l - r);
            else if(op == '*')
                st.emplace(l * r);
            else if(op == '/') {
                if(isZero(r))
                    throw dividedByZeroException {};
                else
                    st.emplace(l / r);
            }
        }
    }

    public :
    static double evaluate (const string& expression) {
        for(auto &ch : expression)
            if(!isValid(ch))
                throw invalidCharacterException {};
        stack<double> number;
        stack<char> op;
        bool may_be_unary = true;
        for(size_t i = 0; i < expression.size(); ++i) {
            if(delim(expression[i])) continue;

            if(expression[i] == '(') {
                op.emplace('(');
                may_be_unary = true;
            } else if(expression[i] == ')') {
                while(!op.empty() && op.top() != '(') {
                    calcWithOperator(number, op.top());
                    op.pop();
                }
                if(op.empty() || op.top() != '(')
                    throw bracketMismatchException {};
                op.pop();
                may_be_unary = false;
            } else if(isOperator(expression[i])) {
                char cur_op = expression[i];
                if(may_be_unary && isUnary(cur_op)) cur_op = -cur_op;
                while(!op.empty() &&
                      ((cur_op >= 0 && opPriority(op.top()) >= opPriority(cur_op)) ||
                      (cur_op < 0 && opPriority(op.top()) > opPriority(cur_op)))) {
                    calcWithOperator(number, op.top());
                    op.pop();
                }
                op.emplace(cur_op);
                may_be_unary = true;
            } else {
                number.emplace(getNum(expression, i));
                may_be_unary = false;
            }
        }
        while(!op.empty()) {
            calcWithOperator(number, op.top());
            op.pop();
        }
        if(number.size() == 1)  return number.top();
        else throw operatorMismatchException {};
    }
};



#endif