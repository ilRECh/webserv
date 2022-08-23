#pragma once

#include "ABlock.hpp"
#include <map>

class LocationBlock;

class ServerBlock : public ABlock
{
private:
    ServerBlock(ServerBlock &that);
    ServerBlock& operator=(ServerBlock &that);

    static const char * params[];

    std::string Host;
    std::string Port;
    std::string Server_name;
    int Client_body_size;
    std::string Index_file;
    std::map<int, std::string> Error_pages;
    LocationBlock * location;

    virtual void parse_block_parameter(); //override
    virtual void validate_parameter_value(); //override

public:
    virtual ~ServerBlock(); //override
    virtual void validate(); //override
};
