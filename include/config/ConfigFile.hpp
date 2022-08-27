#pragma once

#include "logger.hpp"
#include "Server.hpp"
#include <fstream>
#include <vector>
#include <map>

class ServerBlock;

class ConfigFile
{
private:
    ConfigFile();
    ConfigFile(ConfigFile& that);
    ConfigFile &operator=(ConfigFile& that);

    std::ifstream Config_file;
    std::map<std::pair<std::string, std::string>, std::vector<ServerBlock *> > Instances;

    bool find_similar_server_name(std::vector<ServerBlock *> blocks, ServerBlock & block);
std::map<std::pair<std::string, std::string>, std::vector<ServerBlock *> >::iterator 
    find_similar_addresses(ServerBlock & block);

public:
    ConfigFile(std::string const path_to_config_file);
    ~ConfigFile();

    bool good();
    void read_file();
    std::string getline_trimmed();
    std::vector<Server *> get_servers();
};
