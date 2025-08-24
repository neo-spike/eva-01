#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_set>
#include <stack>
#include <math.h>
#include <ctime>
#include <unistd.h>
#include <dirent.h>
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#endif
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <sys/stat.h>
#include <sys/types.h>
#endif

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
    std::string description() const override { return "Just a simple calculator."; };
    int precedence(std::string c);
    std::vector<std::string> postfix(std::vector<std::string> args);
    long double solvePostfix(std::vector<std::string> expression);
    bool isNumber(const std::string &s);
    bool isLeftAssociative(char op);
};

class Time : public TerminalDogma
{
public:
    void execute(const std::vector<std::string> &args) override;
    std::string description() const override { return "It just shows you the time."; };
};

class Clear : public TerminalDogma
{
public:
    void execute(const std::vector<std::string> &args) override;
    std::string description() const override { return "Clears the console."; };
};

class MakeDirectory : public TerminalDogma
{
public:
    void execute(const std::vector<std::string> &args) override;
    std::string description() const override
    {
#if defined(_WIN32) || defined(_WIN64)
        return "It makes directory. Command - forge <directory>";
#else
        return "It makes directory. Command - forge [-a|-s] <directory>";
#endif
    };
    std::vector<std::string> splitPath(const std::string &path);
};

class ChangeDirectory : public TerminalDogma
{
public:
    void execute(const std::vector<std::string> &args) override;
    std::string description() const override { return "Changes the directory to the given directory."; };
};

class DeleteDirectory : public TerminalDogma
{
    public:
    void execute(const std::vector<std::string> &args) override;
    std::string description() const override { return "Changes the directory to the given directory."; };
};

class Show : public TerminalDogma{
public:
    void execute(const std::vector<std::string> &args) override;
    std::string description() const override { return "Changes the directory to the given directory."; };
};
