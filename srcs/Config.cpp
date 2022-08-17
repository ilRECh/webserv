#include "Config.hpp"

Config::Config(std::string const path_to_config_file)
    :   Config_file(path_to_config_file.c_str())
{
    if (Config_file.fail())
    {
        throw ERR("Fail");
    }

    read_file();

    

    Config_file.close();
}

void Config::read_file()
{

}

