#pragma once

#include "logger.hpp"
#include "Server.hpp"
#include <fstream>
#include <map>

class ServerBlock;

class ConfigFile
{
private:
    ConfigFile();
    ConfigFile(ConfigFile& that);
    ConfigFile &operator=(ConfigFile& that);

    std::ifstream Config_file;
    std::map<std::string, ServerBlock *> Instances;
    static const char * location_params[];

public:
    ConfigFile(std::string const path_to_config_file);
    ~ConfigFile();

    bool good();
    void read_file();
    std::string getline_trimmed();
};
