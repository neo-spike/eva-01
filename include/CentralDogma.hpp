#pragma once
#include <unordered_map>
#include <memory>
#include <vector>

class TerminalDogma;

class CentralDogma{
    std::unordered_map<std::string, std::unique_ptr<TerminalDogma>> registry;
public:
    void registerCommand(const std::string& name, std::unique_ptr<TerminalDogma> cmd);
    bool executeCommand(const std::string& name, const std::vector<std::string>& args);

    // to be used by help
    const std::unordered_map<std::string, std::unique_ptr<TerminalDogma>>& getRegistry() const {
        return registry;
    }
};