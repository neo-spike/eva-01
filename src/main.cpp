#include "CentralDogma.hpp"
#include "TerminalDogma.hpp"
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& command){
    std::vector<std::string> tokens;
    std::string token;
    for (size_t i=0; i<command.length(); i++){
        if (command[i]!=' '){
            token+=command[i];
        }
        else{
            if (token.size() != 0){
                tokens.push_back(token);
                token.clear();
            }
        }
    }
    if (token.size()!=0) tokens.push_back(token);

    return tokens;
}


int main(){
    CentralDogma core;

    // registering the commands
    core.registerCommand("say", std::make_unique<Say>());
    core.registerCommand("help", std::make_unique<Help>(core));
    core.registerCommand("calc", std::make_unique<Calculate>());

    std::string command;
    while (true) {
        std::cout << "eva-01> ";

        std::getline(std::cin, command);
        std::vector<std::string> args = split(command);

        if (args.empty()) continue;

        if (args[0] == "exit") break;

        if (!core.executeCommand(args[0], args)) {
            std::cout << "Unknown command: " << args[0] << "\n";
        }
    }
    return 0;
}