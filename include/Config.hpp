#pragma once

#include "stdlibs.hpp"
#include <fstream>

class Config
{
private:
    Config();
    std::ifstream Config_file;

    std::string Server_name;
    std::string Listen;

    void read_file();

public:
    Config(std::string const path_to_config_file);

};
