#include <iostream>
#include <string>
#include <stack>



int main()
{
    std::string input;
    char prethodni = '{';
    std::stack<char> zagrade;

    std::getline(std::cin, input);

    for (char c : input)
    {
        if (c == '{' && prethodni != '[' && prethodni != '(' && prethodni != '<')
        {
            zagrade.push(c);
        }
        else if (c == '[' && prethodni != '(' && prethodni != '<')
        {
            zagrade.push(c);
        }
        else if (c == '(' && prethodni != '<')
        {
            zagrade.push(c);
        }
        else if (c == '<')
        {
            zagrade.push(c);
        }
        else if (c == '}' || c == ']' || c == ')' || c == '>')
        {
            if (!zagrade.empty() && ((c == '}' && zagrade.top() == '{') ||
                                      (c == ']' && zagrade.top() == '[') ||
                                      (c == ')' && zagrade.top() == '(') ||
                                      (c == '>' && zagrade.top() == '<')))
            {
                zagrade.pop();
            }
            else
            {
                std::cout << "Greska";
                return 1;
            }
        }
        else
        {
            std::cout << "Greska";
            return 1;
        }
        prethodni = c;
    }
    std::cout << "Korektno";

    return 0;
}
