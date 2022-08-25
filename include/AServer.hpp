#pragma once

#include <string>
#include <set>
#include <map>

class LocationBlock;
class ServerBlock;

class AServer
{
protected:
    size_t Client_body_size;
    std::string Host;
    std::string Port;
    std::set<std::string> Server_names;
    std::map<int, std::string> Error_pages;
    std::map<std::string, LocationBlock *> Locations;
public:
    AServer() : Client_body_size(1000) {} ;
    AServer(std::string const name ,
            std::string const host ,
            std::string const port)
        :   Client_body_size(1000),
            Host(host),
            Port(port)
    {
        Server_names.insert(name);
    }

    virtual ~AServer() {} ;
};
