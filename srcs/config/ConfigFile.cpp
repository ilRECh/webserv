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

    std::map<std::pair<std::string, std::string>, std::vector<ServerBlock *> >::iterator
        instance = Instances.begin();
    while (instance != Instances.end())
    {
        std::vector<ServerBlock *>::iterator block = instance->second.begin();
        while (block != instance->second.end())
        {
            delete *block;
            ++block;
        }

        ++instance;
    }

    OUT_DBG("Destructor");
}

bool ConfigFile::good()
{
    return Config_file.good();
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

                std::map<std::pair<std::string, std::string>, std::vector<ServerBlock *> >::iterator
                    similar_address = find_similar_addresses(*block);
                if (similar_address != Instances.end())
                {
                    if (not find_similar_server_name(similar_address->second, *block))
                    {
                        similar_address->second.push_back(block);
                    }
                    else
                    {
                        OUT("Block dropped");
                        delete block;
                    }
                }
                else
                {
                    Instances.insert(
                        make_pair(
                            make_pair(
                                block->get_host(),
                                block->get_port()
                            ),
                            std::vector<ServerBlock *>()
                        )
                    ).first->second.push_back(block);

                }
            } catch (std::exception &e) {
                OUT("Catched from Server block: " << e.what());
                delete block;
            }
        }
    }
}

std::map<std::pair<std::string, std::string>, std::vector<ServerBlock *> >::iterator 
    ConfigFile::find_similar_addresses(ServerBlock & block)
{
    addrinfo *instance_net_info;
    addrinfo *server_net_info;
    addrinfo hints;
    memset(&hints, 0, sizeof hints);
    
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    getaddrinfo(block.get_host().c_str(), block.get_port().c_str(), &hints, &instance_net_info);
    
    std::map<std::pair<std::string, std::string>, std::vector<ServerBlock *> >::iterator instance = Instances.begin();
    while (instance != Instances.end())
    {
        getaddrinfo(instance->first.first.c_str(), instance->first.second.c_str(), &hints, &server_net_info);

        if (server_net_info and server_net_info->ai_addr and
            instance_net_info and instance_net_info->ai_addr)
        {
            if (memcmp(server_net_info->ai_addr->sa_data,
                       instance_net_info->ai_addr->sa_data,
                       sizeof(server_net_info->ai_addr->sa_data)) == 0)
            {
                OUT("Similar address for " << NL
                    << block.get_host() << NL
                    << block.get_port() << NL
                    << "found:" << NL
                    << instance->first.first << NL
                    << instance->first.second);
                freeaddrinfo(server_net_info);
                break;
            }
        }

        freeaddrinfo(server_net_info);

        ++instance;
    }

    freeaddrinfo(instance_net_info);

    return instance;
}

bool ConfigFile::find_similar_server_name(std::vector<ServerBlock *> blocks, ServerBlock & new_block)
{
    std::vector<ServerBlock *>::iterator block = blocks.begin();
    while (block != blocks.end())
    {
        std::set<std::string>::iterator name = new_block.get_server_names().begin();
        if (name != new_block.get_server_names().end())
        {
            while (name != new_block.get_server_names().end())
            {
                std::set<std::string>::iterator block_name = (*block)->get_server_names().find(*name);
                if (block_name != (*block)->get_server_names().end())
                {
                    OUT("Similar server name for " << NL
                        << new_block.get_host() << NL
                        << new_block.get_port() << NL
                        << "\"" << *name << "\"" << NL
                        << "found: " << NL
                        << (*block)->get_host() << NL
                        << (*block)->get_port() << NL
                        << (*block_name));
                    
                    return true;
                }

                ++name;
            }
        }
        else if ((*block)->get_server_names().empty())
        {
            OUT("Similar server name for " << NL
            << new_block.get_host() << NL
            << new_block.get_port() << NL
            << "\"\"" << NL
            << "found: " << NL
            << (*block)->get_host() << NL
            << (*block)->get_port());

            return true;
        }

        ++block;
    }

    return false;
}

std::vector<Server *> ConfigFile::get_servers()
{
    if (not Instances.empty())
    {
        std::vector<Server *> servers;
        servers.reserve(Instances.size());

        std::map<std::pair<std::string, std::string>, std::vector<ServerBlock *> >::iterator
            server = Instances.begin();
        while (server != Instances.end())
        {
            Server * new_server = new Server(server->first.first, server->first.second, server->second);

            servers.push_back(new_server);

            ++server;
        }

        return servers; 
    }

    return std::vector<Server *>();
}
