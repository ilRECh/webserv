#pragma once

#include "default.hpp"
#include <string>
#include <set>
#include <map>

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
    std::set<std::string> Server_names;
    std::map<int, std::string> Error_pages;
    std::map<std::string, ALocation *> Locations;

    friend Server;
public:
    AServer(std::string host,
            std::string port)
        :   Client_body_size(DEFAULT_CLIENT_BODY_SIZE),
            Host(host),
            Port(port),
            Server_names(DEFAULT_SERVER_NAMES),
            Error_pages(DEFAULT_ERROR_PAGES),
            Locations(DEFAULT_LOCATIONS)
    {} ;

    AServer()
        :   Client_body_size(DEFAULT_CLIENT_BODY_SIZE),
            Host(DEFAULT_HOST),
            Port(DEFAULT_PORT),
            Server_names(DEFAULT_SERVER_NAMES),
            Error_pages(DEFAULT_ERROR_PAGES),
            Locations(DEFAULT_LOCATIONS)
    {} ;

    AServer(AServer & that)
        :   Client_body_size(that.Client_body_size),
            Host(that.Host),
            Port(that.Port),
            Server_names(that.Server_names),
            Error_pages(that.Error_pages)
    {} ;

    std::string get_host_port() const { return Host + ":" + Port; } ;

    virtual ~AServer() {} ;
};
