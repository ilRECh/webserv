#pragma once

#include <string>
#include <set>
#include <map>

#define DEFAULT_CLIENT_BODY_SIZE 1000

class ALocation;
class Server;

class AServer
{
private:
    AServer & operator=(AServer & that);

protected:
    size_t Client_body_size;
    std::string Host;
    std::string Port;

    std::string Default_server_name;
    std::set<std::string> Server_names;
    
    std::map<int, std::string> Error_pages;
    std::map<std::string, ALocation *> Locations;

    friend Server;
public:
    AServer(std::string host,
            std::string port)
        :   Client_body_size(DEFAULT_CLIENT_BODY_SIZE),
            Host(host),
            Port(port)
    {} ;

    AServer()
        :   Client_body_size(DEFAULT_CLIENT_BODY_SIZE)
    {} ;

    AServer(AServer & that)
        :   Client_body_size(that.Client_body_size),
            Host(that.Host),
            Port(that.Port),
            Default_server_name(that.Default_server_name),
            Server_names(that.Server_names),
            Error_pages(that.Error_pages)
    {} ;

    std::string get_first_name() const { return Default_server_name; } ;

    virtual ~AServer() {} ;
};
