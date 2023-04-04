#include "PostfixCalc.hpp"
#include <cstddef>
#include <sstream>


double PostfixCalc::parse(const std::string &expression)
{

    std::istringstream ss(expression);

    std::string op;
    while (ss >> op)
    {
        if (is_operator(op))
        {
            return do_operation(op);
        }
        else if (is_number(op))
        {
            stek.push(stod(op));
        }
    }
    throw "Expression not valid!";
}



bool PostfixCalc::is_number(const std::string &x)
{
    char *c;
    strtod(x.c_str(), &c);
    return *c == 0;
}

bool PostfixCalc::is_operator(const std::string &c)
{

    return c.find_first_not_of("+-*/") == std::string::npos;
}

double PostfixCalc::do_operation(const std::string &operation)
{
    double lo, ro;


    if (stek.size() < 2)
    {
        throw "Invalid expression!\n";
    }

    ro = stek.top();
    stek.pop();
    lo = stek.top();
    stek.pop();


    if (operation == "+")
    {
        stek.push(lo + ro);
        return lo + ro;
    }

    if (operation == "-")
    {
        stek.push(lo - ro);
        return lo - ro;
    }

    if (operation == "/")
    {
        stek.push(lo / ro);
        return lo / ro;
    }
    
    if (operation == "*")
    {
        stek.push(lo * ro);
        return lo * ro;
    }


    throw "Operacija ne postoji";
}

