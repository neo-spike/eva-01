#include "CentralDogma.hpp"
#include "TerminalDogma.hpp"

void CentralDogma::registerCommand(const std::string& name, std::unique_ptr<TerminalDogma> cmd){
    registry[name]=std::move(cmd);
}

bool CentralDogma::executeCommand(const std::string& name, const std::vector<std::string>& args){
    auto it = registry.find(name);
    if (it!=registry.end()){
        it->second->execute(args);
        return true;
    }
    return false;
}
