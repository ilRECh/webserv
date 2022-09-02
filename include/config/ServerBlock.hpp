#pragma once

#include "ABlock.hpp"
#include "AVirtualServer.hpp"
#include "logger.hpp"
#include <map>
#include <set>

class LocationBlock;
class ConfigFile;

class ServerBlock : public ABlock<ServerBlock>, public AVirtualServer
{
private:
    ServerBlock(ServerBlock &that);
    ServerBlock& operator=(ServerBlock &that);

    void parse_listen(char * value);
    void parse_server_name(char * value);
    void parse_error_page(char * values);
    void parse_client_body_size(char * value);
    void parse_index(char * value);
    void parse_location(char * value);

public:
    ServerBlock(ConfigFile & config);
    virtual ~ServerBlock(); //override
    virtual void validate(); //override
};
