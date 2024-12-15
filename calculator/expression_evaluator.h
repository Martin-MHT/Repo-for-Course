#ifndef EXPRESSION_EVALUATOR
#define EXPRESSION_EVALUATOR
#include <stack>
#include <string>
#include <cctype>
#include <cassert>
#include "calcexceptions.h"
using namespace std;

constexpr double EPS = 1e-18;
constexpr std::size_t MAXSIZE = 10000;


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
    static double getNum(const string& expression, std::size_t &pos) {

        //1. 整数部分
        if(expression[pos] == 'e' || expression[pos] == '.')    //数字不能没有整数部分
            throw invalidInputNumberException {};
        double ret = expression[pos] - '0';
        while(pos + 1 < expression.size() && isdigit(expression[pos + 1]))
            ++pos, ret = ret * 10 + (expression[pos] - '0');

        if(pos + 1 < expression.size() && expression[pos + 1] == '.') { // 2. 小数部分
            ++pos;
            if(pos + 1 == expression.size() || !isdigit(expression[pos + 1])) //有了小数点，之后不能没有数字
                throw invalidInputNumberException {};
            for(double eps = 1.0;
                pos + 1 < expression.size() && isdigit(expression[pos + 1]);
                eps *= 0.1, ret += eps * (expression[++pos] - '0'));
        }
        if(pos + 1 < expression.size() && expression[pos + 1] == 'e') { // 3. 指数部分
            ++pos;
            if(pos + 1 == expression.size() || (!isdigit(expression[pos + 1]) && expression[pos + 1] != '-' && expression[pos + 1] != '+')) // 有了 e，之后不能没有数字
                throw invalidInputNumberException {};
            bool negative = false;
            int exp = 0;
            while(pos + 1 < expression.size() && (expression[pos + 1] == '-' || expression[pos + 1] == '+'))
                negative ^= (expression[++pos] == '-');  // 处理符号问题，如果是正号那么要乘以 10 的幂次，否则需要除去
            for(; pos + 1 < expression.size() && isdigit(expression[pos + 1]);
                  exp = exp * 10 + (expression[++pos] - '0'));
            for(double temp = negative ? 0.1 : 10.0; exp; exp >>= 1, temp = temp * temp)
               if(exp & 1) ret *= temp;
        }
        if(pos + 1 < expression.size() && (expression[pos + 1] == 'e' || expression[pos + 1] == '.')) //不能有多于的 '.' 和 'e'
            throw invalidInputNumberException {};
        return ret;
    }

    static void calcWithOperator(stack<double>& st, char op) { // 处理四则运算
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
        if(expression.size() > MAXSIZE) // 限制表达式长度
            throw expressionSizeOutOfBoundsException {};
        for(auto &ch : expression) // 判断是否有非法字符
            if(!isValid(ch))
                throw invalidCharacterException {};
        stack<double> number;
        stack<char> op;
        bool may_be_unary = true; // 判断是否可能出现正负号 
        for(std::size_t i = 0; i < expression.size(); ++i) {
            if(delim(expression[i])) continue; // 忽略空格 

            if(expression[i] == '(') { // 是左括号，将其压入运算符栈
                op.emplace('(');
                may_be_unary = true;
            } else if(expression[i] == ')') { //是右括号，取出栈顶的运算符并进行运算，直至栈顶出现左括号
                while(!op.empty() && op.top() != '(') {
                    calcWithOperator(number, op.top());
                    op.pop();
                }
                if(op.empty() || op.top() != '(')
                    throw bracketMismatchException {};
                op.pop();
                may_be_unary = false;
            } else if(isOperator(expression[i])) {  //是运算符，先把运算符栈顶处所有优先级更高的运算符取出并求值，然后再将当前运算符压入栈中
                char cur_op = expression[i];
                if(may_be_unary && isUnary(cur_op)) cur_op = -cur_op; // 处理正负号
                while(!op.empty() &&
                      ((cur_op >= 0 && opPriority(op.top()) >= opPriority(cur_op)) ||
                      (cur_op < 0 && opPriority(op.top()) > opPriority(cur_op)))) {
                    calcWithOperator(number, op.top());
                    op.pop();
                }
                op.emplace(cur_op);
                may_be_unary = true;
            } else { // 只能是数字了，调用获取数字的模块
                number.emplace(getNum(expression, i));
                may_be_unary = false;
            }
        }
        while(!op.empty()) { // 处理剩余的四则运算符 
            calcWithOperator(number, op.top());
            op.pop();
        }
        if(number.size() == 1)  return number.top(); // 最后理应只剩下一个元素
        else throw operatorMismatchException {};
    }
};



#endif