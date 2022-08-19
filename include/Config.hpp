#pragma once

#include "logger.hpp"
#include "Server.hpp"
#include "ServerInstance.hpp"
#include <fstream>
#include <map>

class Config
{
private:
    Config();
    Config(Config& that);
    Config &operator=(Config& that);

    std::ifstream Config_file;
    std::map<std::string, ServerInstance> Instances;

    void read_file();
    void add_server_instance();
    void parse_server_instance();

public:
    Config(std::string const path_to_config_file);

};
