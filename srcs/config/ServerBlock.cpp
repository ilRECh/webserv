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
ServerBlock::ServerBlock()
    :   ABlock()
{
    //host:port
    parsers.push_back(
        ABlock::ParamCallback("listen " , std::mem_fun(&ServerBlock::parse_listen), this)
    );

    //name [name [name] ...]
    parsers.push_back(
        ABlock::ParamCallback("server_name "  , std::mem_fun(&ServerBlock::parse_server_name), this)
    );

    //code path
    parsers.push_back(
        ABlock::ParamCallback("error_page " , std::mem_fun(&ServerBlock::parse_error_page), this)
    );

    //num
    parsers.push_back(
        ABlock::ParamCallback("client_body_size " , std::mem_fun(&ServerBlock::parse_client_body_size), this)
    );

    //location path { ... }
    parsers.push_back(
        ABlock::ParamCallback("location " , std::mem_fun(&ServerBlock::parse_location), this)
    );
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
    if (Host.empty() and Port.empty())
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

            if (host.empty())
            {
                host = "127.0.0.1";
            }

            port = value.substr(delimiter_pos + 1, value.length());
        }
        else
        {
            host = "127.0.0.1";
            port = value;
        }

        Host = host;
        Port = port;
    }
}

void ServerBlock::parse_server_name(std::string value)
{
    char * value_buf = new char[value.length() + 1];

    strcpy(value_buf, value.c_str());

    char * name = std::strtok(value_buf, " ");

    while (name != NULL)
    {
        Server_name.insert(name);
        name = std::strtok(NULL, " ");
    }

    delete value_buf;
}

void ServerBlock::parse_error_page(std::string value)
{
    (void)value;
}

void ServerBlock::parse_client_body_size(std::string value)
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
