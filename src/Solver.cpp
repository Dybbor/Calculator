#include "Solver.h"
#include <stdexcept>
#include <cmath>
#include <iostream>

Solver::Solver(std::string _infix) : infix{ _infix } {}

int Solver::GetPriorityOperation(const char operation) const
{
    int priority;
    switch (operation) {
    case '(':
        priority = 0;
        break;
    case '+':
        priority = 1;
        break;
    case '-':
        priority = 1;
        break;
    case '*':
        priority = 2;
        break;
    case '/':
        priority = 2;
        break;
    case '^':
        priority = 3;
        break;
    case 's':
        priority = 4;
        break;
    case 'c':
        priority = 4;
        break;
    case 't':
        priority = 4;
        break;
    default: throw std::invalid_argument("invalide operation: " + operation);
    }
    return priority;
}

void Solver::ToPostfix()
{
    postfix = "";
    stackOperation = std::stack<char>();
    std::string tmp = "(" + infix + ")";
    for (int i = 0; i < tmp.size(); i++)
    {
        if (tmp[i] == '(')
            stackOperation.push(tmp[i]);
        if (tmp[i] >= '0' && tmp[i] <= '9' || tmp[i] == '.')
            postfix += tmp[i];
        if (tmp[i] == ')')
        {
            while (stackOperation.top() != '(') {
                postfix += stackOperation.top();
                stackOperation.pop();
            }
            stackOperation.pop();
        }
        if (tmp[i] == '+' || tmp[i] == '-' || tmp[i] == '*' || tmp[i] == '/' || tmp[i] == '^')
        {
            postfix += ' ';
            while (GetPriorityOperation(tmp[i]) <= GetPriorityOperation(stackOperation.top()))
            {
                postfix += stackOperation.top();
                stackOperation.pop();
            }
            stackOperation.push(tmp[i]);
        }
        if (tmp[i] == 's' || tmp[i] == 'c' || tmp[i] == 't')
        {
            if (i == tmp.find("sin") || i == tmp.find("cos") || i == tmp.find("tg"))
            {
                stackOperation.push(tmp[i]);
                if (tmp[i] == 's' || tmp[i] == 'c')
                    i += 2;
                else
                    i++;
            }
            else
                throw std::invalid_argument("can't present in postfix: check input data");
        }
    }
}

void Solver::SetInfix()
{
}

bool Solver::CheckBrackets() const
{
    std::stack<char> brackets;
    if (infix.size() == 0) {
        throw std::invalid_argument("infix size can't be zero");
    }
    for (const auto& symbol : infix) {
        if (symbol == '(') {
            brackets.push(symbol);
        }
        else if (symbol == ')') {
            if (brackets.empty()) {
                return false;
            }
            else {
                brackets.pop();
            }
        }
    }
    return brackets.empty() ? true : false;
}

bool Solver::CheckOperation() const
{
    if (infix.size() == 0) {
        std::invalid_argument("String is empty");
    }
    if (infix[0] == '+' || infix[0] == '-' || infix[0] == '*' || infix[0] == '/')
        return false;
    if (infix[infix.size() - 1] == '+' || infix[infix.size() - 1] == '-' || infix[infix.size() - 1] == '*'
        || infix[infix.size() - 1] == '/') {
        return false;
    }
    for (int i = 0; i < infix.size() - 1; i++) {
        if ((infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') &&
            (infix[i + 1] == '+' || infix[i + 1] == '-' || infix[i + 1] == '*' || infix[i + 1] == '/' || infix[i + 1] == '^'))
            return false;
    }
    return true;
}

std::string Solver::getPostfix()
{
    return postfix;
}

double Solver::Calculate()
{
    if (!CheckBrackets())
        throw std::invalid_argument("Check brackets");
    if (!CheckOperation()) {
        throw std::invalid_argument("Check operation");
    }
    ToPostfix();
    double num1, num2, res, tmp;
    int size = postfix.size();
    if (size == 0)
        throw std::invalid_argument("expression can't be zero size");

    stackNumbers = std::stack<double>();
    for (int i = 0; i < postfix.size(); i++)
    {
        if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^')
        {
            num2 = stackNumbers.top();
            stackNumbers.pop();
            num1 = stackNumbers.top();
            stackNumbers.pop();
            switch (postfix[i])
            {
            case '+':
                res = num1 + num2;
                break;
            case '-':
                res = num1 - num2;
                break;
            case '*':
                res = num1 * num2;
                break;
            case '/':
                res = num1 / num2;
                break;
            case '^':
                res = pow(num1, num2);
                break;

            }
            stackNumbers.push(res);
        }
        if (postfix[i] >= '0' && postfix[i] <= '9')
        {
            char* p;
            double x;
            x = strtod(&postfix[i], &p);
            stackNumbers.push(x);
            int Lenght = p - &postfix[i];
            i += Lenght - 1;
        }
        if (postfix[i] == 's' || postfix[i] == 'c' || postfix[i] == 't')
        {
            switch (postfix[i])
            {
            case 's':
                res = std::sin(stackNumbers.top());
                stackNumbers.pop();
                stackNumbers.push(res);
                break;
            case 'c':
                res = std::cos(stackNumbers.top());
                stackNumbers.pop();
                stackNumbers.push(res);
                break;
            case 't':
                res = tan(stackNumbers.top());
                stackNumbers.pop();
                stackNumbers.push(res);
                break;
            }
        }
    }
    tmp = stackNumbers.top();
    stackNumbers.pop();
    if (stackNumbers.empty())
        return tmp;
    else
        std::invalid_argument("Check input data");
}
