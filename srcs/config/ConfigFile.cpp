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

    std::vector<ServerBlock *>::iterator instance = Instances.begin();
    while (instance != Instances.end())
    {
        delete (*instance);
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
#if 0
                switch (find_duplicates_in(Instances, *block))
                {
                    case INSTANCE_IS_DEFAULT:
                        block->mark_default();
                        Instances.push_back(block);
                        break;
                    case REGULAR_INSTANCE:
                        Instances.push_back(block);
                        break;
                    case DUPLICATE:
                        delete block;
                    default:
                        break;
                }
                // if ((block->get_first_name()) == Instances.end())
                // {
                //    Instances.insert(make_pair(block->get_first_name(), block));
                // }
                // else
                // {
                //    delete block;
                // }
#else
delete block;
#endif
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

ConfigFile::BlockProperty ConfigFile::find_duplicates_in(std::vector<ServerBlock *> & instances,
                                                         ServerBlock & block)
{
    addrinfo hints;
    memset(&hints, 0, sizeof hints);
    
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    (void)block;
    std::vector<ServerBlock *>::iterator instance = instances.begin();
    while (instance != instances.end())
    {
//TODO: getaddrinfo comparing, then compare sets
    }

    return INSTANCE_IS_DEFAULT;
}

std::vector<Server *> ConfigFile::get_servers()
{
    if (not Instances.empty())
    {
        std::vector<Server *> servers;
        servers.reserve(Instances.size());

        std::vector<ServerBlock *>::iterator server = Instances.begin();
        while (server != Instances.end())
        {
            Server * new_server = new Server(**server);

            servers.push_back(new_server);

            ++server;
        }

        return servers; 
    }

    return std::vector<Server *>();
}
