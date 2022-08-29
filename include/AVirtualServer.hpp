#pragma once

#include <string>
#include <set>
#include <map>

#define DEFAULT_CLIENT_BODY_SIZE 1000

class ALocation;
class Server;

class AVirtualServer
{
private:
    AVirtualServer & operator=(AVirtualServer & that);

protected:
    std::string Host;
    std::string Port;
    size_t Client_body_size;
    std::set<std::string> Server_names;
    std::map<int, std::string> Error_pages;
    std::map<std::string, ALocation *> Locations;

    friend Server;
public:
    AVirtualServer(std::string host,
                   std::string port)
        :   Host(host),
            Port(port),
            Client_body_size(DEFAULT_CLIENT_BODY_SIZE)
    {}

    AVirtualServer()
        :   Host(),
            Port(),
            Client_body_size(DEFAULT_CLIENT_BODY_SIZE)
    {}

    AVirtualServer(AVirtualServer & that)
        :   Host(that.Host),
            Port(that.Port),
            Client_body_size(that.Client_body_size),
            Server_names(that.Server_names),
            Error_pages(that.Error_pages)
    {} ;

    std::string const & get_host() const
    {
        return Host;
    }

    std::string const & get_port() const
    {
        return Port;
    }

    size_t const & get_client_body_size() const
    {
        return Client_body_size;
    }

    std::set<std::string> const & get_server_names() const
    {
        return Server_names;
    }

    std::map<int, std::string> const & get_error_pages() const
    {
        return Error_pages;
    }

    std::map<std::string, ALocation *> const & get_locations() const 
    {
        return Locations;
    }

    virtual ~AVirtualServer() {} ;
};
