#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_set>
#include <stack>
#include <math.h>

class CentralDogma;

class TerminalDogma
{
public:
    virtual ~TerminalDogma() {};
    virtual void execute(const std::vector<std::string> &args) = 0;
    virtual std::string description() const = 0;
};

class Say : public TerminalDogma
{
public:
    void execute(const std::vector<std::string> &args) override;
    std::string description() const override { return "Prints text to the console"; }
};

class Help : public TerminalDogma
{
    CentralDogma &core;

public:
    Help(CentralDogma &c) : core(c) {};
    void execute(const std::vector<std::string> &args) override;
    std::string description() const override { return "Gives information about the commands"; };
};

class Calculate : public TerminalDogma
{
    std::unordered_set<char> operators = {'+', '-', '*', '/', '%', '^'};

public:
    void execute(const std::vector<std::string> &args) override;
    std::string description() const override { return "Can't you see it is a calculator!!"; };
    int precedence(std::string c);
    std::vector<std::string> postfix(std::vector<std::string> args);
    long double solvePostfix(std::vector<std::string> expression);
    bool isNumber(const std::string &s)
    {
        if (s.empty())
            return false;

        bool hasDecimal = false;
        for (char c : s)
        {
            if (c == '.')
            {
                if (hasDecimal)
                    return false;
                hasDecimal = true;
            }
            else if (!isdigit(c))
            {
                return false;
            }
        }
        return true;
    }
    bool isLeftAssociative(char op)
    {
        if (op == '^')
            return false; 
        return true;      
    }
};