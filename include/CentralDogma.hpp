#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <cstdlib>
#include <fstream> 
#include <list>
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#else
    #include <limits.h>
    #include <unistd.h>
#endif

class TerminalDogma;

class CentralDogma{
private:
    std::unordered_map<std::string, std::unique_ptr<TerminalDogma>> registry;

    // history parts
    std::list<std::vector<std::string>> historyList;
    // Iterator to navigate history using ↑ and ↓
    std::list<std::vector<std::string>>::iterator currentHistory;
    std::unordered_map<std::string, std::vector<std::list<std::vector<std::string>>::iterator>> historyIndex;

    std::string configPath;
    std::string username="";

public:
    CentralDogma();
    void registerCommand(const std::string& name, std::unique_ptr<TerminalDogma> cmd);
    bool executeCommand(const std::string& name, const std::vector<std::string>& args);

    // to be used by help
    const std::unordered_map<std::string, std::unique_ptr<TerminalDogma>>& getRegistry() const {
        return registry;
    }
    std::string getUsername();
    std::string workingDirectory();
    bool parseCommand(const std::vector<std::string>& args);

    // history functions
    void addToHistory(const std::vector<std::string>& args);
};