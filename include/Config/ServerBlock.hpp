#pragma once

#include "ABlock.hpp"
#include "logger.hpp"
#include <map>
#include <set>

class LocationBlock;

class ServerBlock : public ABlock
{
private:
    ServerBlock(ServerBlock &that);
    ServerBlock& operator=(ServerBlock &that);

    static ABlock::ParamCallback parsers_setup[];

    std::string Host;
    std::string Port;
    std::set<std::string> Server_name;
    int Client_body_size;
    std::string Index_file;
    std::map<int, std::string> Error_pages;
    LocationBlock * location;

    static void parse_listen(std::string value);
    static void parse_server_name(std::string value);
    static void parse_error_page(std::string value);
    static void parse_client_body_size(std::string value);
    static void parse_index(std::string value);
    static void parse_location(std::string value);

public:
    ServerBlock();
    virtual ~ServerBlock(); //override
    virtual void validate(); //override
};
