#include "Config.hpp"
#include "ServerBlock.hpp"

Config::Config(std::string const path_to_config_file)
    :   Config_file(path_to_config_file.c_str())
{
    if (Config_file.fail())
    {
        throw ERR("Config opening error");
    }

    OUT_DBG("Constructor");
}

Config::~Config()
{
    Config_file.close();

    std::map<std::string, ServerBlock *>::iterator instance = Instances.begin();
    while (instance != Instances.end())
    {
        delete instance->second;
        ++instance;
    }

    OUT_DBG("Destructor");
}

bool Config::good()
{
    return Config_file.good();
}

void Config::read_file()
{
    while (Config_file.good())
    {
        if (getline_trimmed() == "server {")
        {
            ServerBlock *block = new ServerBlock();
            try {
                block->parse_block(*this);
                block->validate();
            } catch (std::exception &e) {
                delete block;
                throw;
            }

            //if (Instances.find() != Instances.end())
            //{
            //    Instances.insert(make_pair(block.get_host() + ":" + block.get_port(), block));
            //}
            //else
            //{
            //    delete block;
            //}
        }
    }
}

std::string Config::getline_trimmed()
{
    char const * whitespaces = "\x07\x08\x09\x0A\x0B\x0C\x0D\x20";
    std::string line;
    size_t pos = 0;

    if (Config_file.good())
    {
        std::getline(Config_file, line);

        if ((pos = line.find_first_not_of(whitespaces)) != line.npos)
        {
            line.erase(0, pos);
        }

        if ((pos = line.find_last_not_of(whitespaces)) != line.npos)
        {
            line.erase(pos + 1, line.length());
        }
    }
    else
    {
        throw ERR("Getline failed");
    }

    return line;
}
