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

    static void parse_listen();
    static void parse_server_name();
    static void parse_error_page();
    static void parse_client_body_size();
    static void parse_index();
    static void parse_location();

    virtual void parse_block_parameter(); //override
    virtual void validate_parameter_value(); //override
public:
    ServerBlock();
    virtual ~ServerBlock(); //override
    virtual void validate(); //override
};
