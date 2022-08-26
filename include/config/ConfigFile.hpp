#pragma once

#include "logger.hpp"
#include "Server.hpp"
#include <fstream>
#include <vector>

class ServerBlock;

class ConfigFile
{
private:
    ConfigFile();
    ConfigFile(ConfigFile& that);
    ConfigFile &operator=(ConfigFile& that);

    std::ifstream Config_file;
    std::vector<ServerBlock *> Instances;

    enum BlockProperty
    {
        INSTANCE_IS_DEFAULT ,
        REGULAR_INSTANCE    ,
        DUPLICATE
    };

public:
    ConfigFile(std::string const path_to_config_file);
    ~ConfigFile();

    bool good();
    void read_file();
    std::string getline_trimmed();
    BlockProperty find_duplicates_in(std::vector<ServerBlock *> & instances, ServerBlock & block);
    std::vector<Server *> get_servers();
};
