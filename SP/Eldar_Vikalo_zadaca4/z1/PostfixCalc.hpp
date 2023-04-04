#pragma once
#include <iostream>
#include <stack>
#include <string>



class PostfixCalc
{
private:
    std::stack<double> stek;
    bool is_operator(const std::string &);
    bool is_number(const std::string &);
    double do_operation(const std::string &);

public:
    double parse(const std::string &);
};
