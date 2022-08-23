#pragma once

#include "logger.hpp"
#include "Server.hpp"
#include <fstream>
#include <map>

class ServerBlock;

class Config
{
private:
    Config();
    Config(Config& that);
    Config &operator=(Config& that);

    std::ifstream Config_file;
    std::map<std::string, ServerBlock *> Instances;
    static const char * location_params[];

public:
    Config(std::string const path_to_config_file);
    ~Config();

    bool good();
    void read_file();
    std::string getline_trimmed();
};
