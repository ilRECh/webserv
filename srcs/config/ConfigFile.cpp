#include "ConfigFile.hpp"
#include "ServerBlock.hpp"

ConfigFile::ConfigFile(std::string const path_to_config_file)
    :   Config_file(path_to_config_file.c_str())
{
    if (Config_file.fail())
    {
        throw ERR("Config opening error");
    }

    OUT_DBG("Constructor");
}

ConfigFile::~ConfigFile()
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

bool ConfigFile::good()
{
    return Config_file.good();
}

void ConfigFile::read_file()
{
    while (Config_file.good())
    {
        if (getline_trimmed() == "server {")
        {
            ServerBlock *block = new ServerBlock(*this);

            try {
                block->parse_block();
                block->validate();

                if (Instances.find(block->get_host_port()) == Instances.end())
                {
                   Instances.insert(make_pair(block->get_host_port(), block));
                }
                else
                {
                   delete block;
                }
            } catch (std::exception &e) {
                OUT("Catched from Server block: " << e.what());
                delete block;
            }
        }
    }
}

std::string ConfigFile::getline_trimmed()
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

std::vector<Server *> ConfigFile::get_servers()
{
    if (not Instances.empty())
    {
        std::vector<Server *> servers;
        servers.reserve(Instances.size());

        std::map<std::string, ServerBlock *>::iterator server = Instances.begin();
        while (server != Instances.end())
        {
            Server * new_server = new Server(*(server->second));

            servers.push_back(new_server);

            ++server;
        }

        return servers; 
    }

    return std::vector<Server *>();
}
