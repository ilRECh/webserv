#include "ServerBlock.hpp"
#include "LocationBlock.hpp"
#include <algorithm>
#include <cstring>

/**
 * @brief server block
 * listen           - choose the port and host
 * server_name      - setup or not
 * error_page       - setup default error pages
 * client_body_size - limit client body size
 * index            - default page when accessing the basic url, if provided
 * location         - setup routes with one or multiple of the following
 * 
 */
ABlock::ParamCallback ServerBlock::parsers_setup[] =
{
    { "listen "           , ServerBlock::parse_listen           } , //host:port
    { "server_name "      , ServerBlock::parse_server_name      } , //name [name [name] ...]
    { "error_page "       , ServerBlock::parse_error_page       } , //code path
    { "client_body_size " , ServerBlock::parse_client_body_size } , //num
    { "index "            , ServerBlock::parse_index            } , //path
    { "location "         , ServerBlock::parse_location         }   //location path { ... }
};

ServerBlock::ServerBlock()
    :   ABlock(parsers_setup, parsers_setup + (sizeof(parsers_setup) / sizeof(ABlock::ParamCallback)))
{
    OUT_DBG("Constructor");
}

ServerBlock::~ServerBlock()
{
    std::map<std::string, LocationBlock *>::iterator location = Locations.begin();
    while (location != Locations.end())
    {
        delete location->second;
        ++location;
    }

    OUT_DBG("Destructor");
}

void ServerBlock::parse_listen(std::string value)
{
    const char * msg = "Invalid host:port value of the listen parameter";
    std::string host;
    std::string port;
    size_t delimiter_pos = value.find(':');

    if (delimiter_pos != value.npos)
    {
        if (delimiter_pos != value.rfind(':'))
        {
            throw ERR(msg);
        }

        host = value.substr(0, delimiter_pos);
        port = value.substr(delimiter_pos + 1, value.length());
    }
    else
    {
        host = "127.0.0.1";
        port = value;
    }

    if (host != "127.0.0.1")
    {
        std::list<std::string> octets;
        char * host_copy = new char[host.size() + 1];

        strcpy(host_copy, host.c_str());

        char * octet = std::strtok(host_copy, ".");

        while (octet != NULL)
        {
            octets.push_back(octet);
            octet = std::strtok(NULL, ".");
        }

        delete host_copy;

        if (octets.size() != 4)
        {
            throw ERR(msg);
        }
    }

    int port_num = std::atoi(port.c_str());

    if (1024 > port_num or port_num > 65536)
    {
        throw ERR(msg);
    }
}

void ServerBlock::parse_server_name(std::string value)
{
    (void)value;
}

void ServerBlock::parse_error_page(std::string value)
{
    (void)value;
}

void ServerBlock::parse_client_body_size(std::string value)
{
    (void)value;
}

void ServerBlock::parse_index(std::string value)
{
    (void)value;
}

void ServerBlock::parse_location(std::string value)
{
    (void)value;
}

void ServerBlock::validate()
{
    if (Host.empty() or Port.empty())
    {
        throw ERR("host:port invalid");
    }
}
