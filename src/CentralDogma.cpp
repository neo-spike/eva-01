#include "CentralDogma.hpp"
#include "TerminalDogma.hpp"

CentralDogma::CentralDogma()
{

#if defined(_WIN32) || defined(_WIN64)
    char hostname[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(hostname);
    if (GetComputerNameA(hostname, &size))
    {
        username = std::string(hostname);
    }
#else
    char hostname[HOST_NAME_MAX];
    if (gethostname(hostname, sizeof(hostname)) == 0)
    {
        username = std::string(hostname);
    }
#endif
    currentHistory = historyList.end();
}

void CentralDogma::registerCommand(const std::string &name, std::unique_ptr<TerminalDogma> cmd)
{
    registry[name] = std::move(cmd);
}

bool CentralDogma::executeCommand(const std::string &name, const std::vector<std::string> &args)
{
    auto it = registry.find(name);
    if (it != registry.end())
    {
        it->second->execute(args);
        return true;
    }
    return false;
}

std::string CentralDogma::getUsername(){
    return username;
}

std::string CentralDogma::workingDirectory()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr)
    {
        std::string path = cwd;
        size_t pos = path.find_last_of("/\\");
        std::string lastDir;
        if (pos != std::string::npos) {
            lastDir = path.substr(pos + 1); 
        } else {
            lastDir = path; 
        }
        return lastDir;
    }
    return "";
}

bool CentralDogma::parseCommand(const std::vector<std::string>& args){
    if (args.empty()) return true;
    if (!executeCommand(args[0], args)){
        return false;
    }
    else{
        addToHistory(args);
        return true;
    }
}

void CentralDogma::addToHistory(const std::vector<std::string>& args){
    
}