#include "Config.hpp"

Config::Config(std::string const path_to_config_file)
{
    std::ifstream config(path_to_config_file.c_str());

    if (config.fail())
    {
        throw ERR("Fail");
    }
}

