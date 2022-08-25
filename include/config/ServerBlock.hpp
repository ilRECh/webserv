#pragma once

#include "ABlock.hpp"
#include "AServer.hpp"
#include "logger.hpp"
#include <map>
#include <set>

class LocationBlock;
class ConfigFile;

class ServerBlock : public ABlock<ServerBlock>, public AServer
{
private:
    ServerBlock(ServerBlock &that);
    ServerBlock& operator=(ServerBlock &that);

    void parse_listen(std::string value);
    void parse_server_name(std::string value);
    void parse_error_page(std::string values);
    void parse_client_body_size(std::string value);
    void parse_index(std::string value);
    void parse_location(std::string value);

public:
    ServerBlock(ConfigFile & config);
    virtual ~ServerBlock(); //override
    virtual void validate(); //override
};
