#pragma once
#include <string>
#include <stack>

class Solver{
private:
    std::string infix, postfix;
    std::stack<char> stackOperation;
    std::stack<double> stackNumbers;
    int GetPriorityOperation(const char operation) const;
    bool CheckOperation() const;
    bool CheckBrackets() const;
    void ToPostfix();
public:
    Solver(std::string _infix);
    Solver(const Solver&) = delete;
    Solver& operator=(const Solver&) = delete;
    ~Solver() = default;
   
    void SetInfix();
public:
    std::string getPostfix();
    double Calculate();
};