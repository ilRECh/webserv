#pragma once

#include "ALocation.hpp"
#include "logger.hpp"
#include <string>
#include <set>
#include <map>

#define DEFAULT_CLIENT_BODY_SIZE 1000000

class Server;

class AVirtualServer
{
private:
    AVirtualServer & operator=(AVirtualServer & that);

protected:
    std::string Host;
    std::string Port;
    size_t Client_max_body_size;
    std::set<std::string> Server_names;
    std::map<int, std::string> Error_pages;
    std::map<std::string, ALocation *> Locations;

    AVirtualServer(std::string host,
                   std::string port)
        :   Host(host),
            Port(port),
            Client_max_body_size(DEFAULT_CLIENT_BODY_SIZE)
    {
        OUT_DBG("Constructor");
    }

    AVirtualServer()
        :   Host(),
            Port(),
            Client_max_body_size(DEFAULT_CLIENT_BODY_SIZE)
    {
        OUT_DBG("Constructor");
    }

    AVirtualServer(AVirtualServer & that)
        :   Host(that.Host),
            Port(that.Port),
            Client_max_body_size(that.Client_max_body_size),
            Server_names(that.Server_names),
            Error_pages(that.Error_pages)
    {
        OUT_DBG("Copy constructor");
    }

public:

    virtual ~AVirtualServer()
    {
        std::map<std::string, ALocation *>::iterator location = Locations.begin();
        while (location != Locations.end())
        {
            delete location->second;
            ++location;
        }

        OUT_DBG("Destructor");
    }

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
        return Client_max_body_size;
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
};
