#pragma once

#include "ABlock.hpp"
#include "logger.hpp"
#include <map>
#include <set>

class LocationBlock;

class ServerBlock : public ABlock<ServerBlock>
{
private:
    ServerBlock(ServerBlock &that);
    ServerBlock& operator=(ServerBlock &that);

    std::string Host;
    std::string Port;
    std::set<std::string> Server_name;
    int Client_body_size;
    std::string Index_file;
    std::map<int, std::string> Error_pages;
    std::map<std::string, LocationBlock *> Locations;

    void parse_listen(std::string value);
    void parse_server_name(std::string value);
    void parse_error_page(std::string value);
    void parse_client_body_size(std::string value);
    void parse_index(std::string value);
    void parse_location(std::string value);

public:
    ServerBlock();
    virtual ~ServerBlock(); //override
    virtual void validate(); //override
};
