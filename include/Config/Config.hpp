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
    static const char * server_params[];
    static const char * location_params[];

    static void getline_trimmed(std::ifstream &input, std::string &line);

    void parse_server_instance();
    void parse_server_instance_parameter(ServerInstance &instance,
                                         std::string &parameter);
    bool examine_server_instance(ServerInstance &instance);
    void add_server_instance(ServerInstance &instance);

public:
    Config(std::string const path_to_config_file);

    void read_file();
};
