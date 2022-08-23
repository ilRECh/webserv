#pragma once

#include "ABlock.hpp"
#include <map>

class LocationBlock;

class ServerBlock : public ABlock
{
private:
    ServerBlock(ServerBlock &that);
    ServerBlock& operator=(ServerBlock &that);

    std::string Host;
    std::string Port;
    std::string Server_name;
    int Client_body_size;
    std::string Index_file;
    std::map<int, std::string> Error_pages;
    LocationBlock * location;
public:
    virtual ~ServerBlock();
};
