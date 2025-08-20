#include "TerminalDogma.hpp"
#include "CentralDogma.hpp"
#include <iostream>

void Say ::execute(const std::vector<std::string> &args)
{
    for (size_t i = 1; i < args.size(); ++i)
    {
        std::cout << args[i] << " ";
    }
    std::cout << "\n";
}

void Help::execute(const std::vector<std::string> &args)
{
    std::cout << "Available commands:\n";
    for (const auto &name : core.getRegistry())
    {
        std::cout << "  " << name.first << " - " << name.second->description() << "\n";
    }
}

int Calculate::precedence(std::string c)
{
    if (c == "^")
        return 3;
    else if (c == "/" || c == "*")
        return 2;
    else if (c == "+" || c == "-")
        return 1;
    else
        return -1;
}

std::vector<std::string> Calculate::postfix(std::vector<std::string> args)
{
    std::stack<std::string> st;
    std::vector<std::string> result;

    for (int i = 0; i < args.size(); i++)
    {
        if (isNumber(args[i]))
        {
            result.push_back(args[i]);
        }
        // handling -> ()
        else if (args[i] == "(")
        {
            st.push(args[i]);
        }
        else if (args[i] == ")")
        {
            while (!st.empty() && st.top() != "(")
            {
                result.push_back(st.top());
                st.pop();
            }
            if (!st.empty())
                st.pop();
        }

        // in case of operators
        else if (operators.count(args[i][0]))
        {
            while (!st.empty() && operators.count(args[i][0]))
            {
                if ((isLeftAssociative(args[i][0]) && precedence(args[i]) <= precedence(st.top())) ||
                    (!isLeftAssociative(args[i][0]) && precedence(args[i]) < precedence(st.top())))
                {
                    result.push_back(st.top());
                    st.pop();
                }
                else
                {
                    break;
                }
            }
            st.push(args[i]);
        }
    }

    while (!st.empty())
    {
        result.push_back(st.top());
        st.pop();
    }

    return result;
}

long double Calculate::solvePostfix(std::vector<std::string> expression)
{
    std::stack<long double> st;
    for (int i = 0; i < expression.size(); i++)
    {
        if (isNumber(expression[i]))
        {
            long double num = std::stold(expression[i]);
            st.push(num);
        }
        else
        {
            long double val1 = st.top();
            st.pop();
            long double val2 = st.top();
            st.pop();
            long double res;
            if (expression[i] == "+")
            {
                res = val1 + val2;
            }
            else if (expression[i] == "-")
            {
                res = val2 - val1;
            }
            else if (expression[i] == "*")
            {
                res = val1 * val2;
            }
            else if (expression[i] == "/")
            {
                res = val2 / val1;
            }
            else if (expression[i] == "^")
            {
                res = pow(val2, val1);
            }
            st.push(res);
        }
    }
    return st.top();
}

void Calculate::execute(const std::vector<std::string> &args)
{
    bool safety = true;
    std::string expression;

    long long nbraces = 0, ops = 0;

    for (int i = 1; i < args.size(); i++)
    {
        expression += args[i];
    }

    std::vector<std::string> tokens;
    std::string token = "";

    int i = 0;
    while (i < expression.size())
    {
        if (expression[i] == '(' || expression[i] == ')' || operators.count(expression[i]))
        {
            token += expression[i];
            tokens.push_back(token);
            if (expression[i] == '(' || expression[i] == ')')
            {
                nbraces++;
            }
            token = "";
            i++;
        }
        else if ((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '.')
        {
            while (!operators.count(expression[i]) && (expression[i] != '(') && (expression[i] != ')') && i < expression.size())
            {
                token += expression[i];
                i++;
            }
            if (isNumber(token))
            {
                tokens.push_back(token);
            }
            else
            {
                safety = false;
                break;
            }
            token = "";
        }
        else
        {
            safety = false;
            break;
        }
    }

    if (nbraces % 2 != 0)
    {
        safety = false;
    }
    else if (tokens.size() <= 2)
    {
        safety = false;
    }
    else
    {
        for (int i = 0; i < tokens.size() - 1; i++)
        {
            if (tokens[i] == "/" && tokens[i + 1] == "0")
            {
                safety = false;
                break;
            }
            // handling negative sign before making the safety falls for other cases
            else if (tokens[i] == "-")
            {
                if (i == 0 || (tokens[i - 1] == "(" && i > 0))
                {
                    tokens.insert(tokens.begin() + i, "0");
                }
                else if (operators.count(tokens[i - 1][0]) && tokens[i - 1] != "-")
                {
                    tokens.insert(tokens.begin() + i, "(");
                    tokens.insert(tokens.begin() + i + 1, "0");
                    int k = i + 3;

                    while (k < tokens.size() &&
                           !operators.count(tokens[k][0]) && tokens[k] != ")" && tokens[k] != "(" && tokens[k]!=".")
                    {
                        k++;
                    }

                    tokens.insert(tokens.begin() + k, ")");
                }
                else if (operators.count(tokens[i + 1][0]))
                {
                    safety = false;
                    break;
                }
                continue;
            }
            else if (operators.count(tokens[0][0]) && tokens[i] != "-")
            {
                safety = false;
            }
            else if (operators.count(tokens[tokens.size() - 1][0]))
            {
                safety = false;
            }
            else if (operators.count(tokens[i][0]) && operators.count(tokens[i + 1][0]) && tokens[i + 1] != "-")
            {
                safety = false;
            }
            else if ((operators.count(tokens[i][0]) && (tokens[i + 1] == ")")) || (tokens[i] == "(") && operators.count(tokens[i + 1][0]) && (tokens[i + 1] != "-"))
            {
                safety = false;
            }
        }
    }

    if (!safety)
    {
        std::cout << "Give Correct expression\n";
    }
    else
    {
        std::cout << solvePostfix(postfix(tokens)) << "\n";
    }
}