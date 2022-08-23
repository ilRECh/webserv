#pragma once

#include "ABlock.hpp"
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

    void parse_listen();
    void parse_server_name();
    void parse_error_page();
    void parse_client_body_size();
    void parse_index();
    void parse_location();

    virtual void parse_block_parameter(); //override
    virtual void validate_parameter_value(); //override
public:
    virtual ~ServerBlock(); //override
    virtual void validate(); //override
};
