#include <iostream>
#include <string>
#include "PostfixCalc.hpp"



int main()
{
    PostfixCalc calculator;
    while (true)
    {
        std::string expression;
        std::cout << " Unesite operacije, ako unesete q izaci cete iz programa";
        std::getline(std::cin, expression);

        if (expression == "q")
            break;
        try
        {
            double result = calculator.parse(expression);

            std::cout << ">> " << result << std::endl;
        }
        catch (char const *e)
        {
            std::cout << e;
        }
    }
    return 0;
}
