#include "Config.hpp"

static void trim(std::string &to_trim)
{
    char const * whitespaces = "\x07\x08\x09\x0A\x0B\x0C\x0D\x20";
    size_t pos = 0;

    if ((pos = to_trim.find_first_not_of(whitespaces)) != to_trim.npos)
    {
        to_trim.erase(0, pos);
    }

    if ((pos = to_trim.find_last_not_of(whitespaces)) != to_trim.npos)
    {
        to_trim.erase(pos + 1, to_trim.length());
    }
}

static void getline_trimmed(std::ifstream &input, std::string &line)
{
    std::getline(input, line);
    trim(line);
}

Config::Config(std::string const path_to_config_file)
    :   Config_file(path_to_config_file.c_str())
{
    if (Config_file.fail())
    {
        throw ERR("Fail");
    }

    try {
        read_file();
    } catch (...) {
        Instances.clear();
    }

    Config_file.close();

    if (Instances.empty())
    {
        throw ERR("Config invalid");
    }
}

void Config::read_file()
{
    std::string line;

    while (Config_file.good())
    {
        getline_trimmed(Config_file, line);

        if (line == "server{" or line == "server {")
        {
            parse_server_instance();
        }
    }
}

void Config::parse_server_instance()
{
    std::string instance_config;
    std::string line;

    while (Config_file.good())
    {
        getline_trimmed(Config_file, line);
        instance_config += line;
        if (Config_file.good() and line == "}")
        {
            break;
        }
        else if (Config_file.bad())
        {

        }
    }
}

