#include "ServerBlock.hpp"
#include "LocationBlock.hpp"
#include <algorithm>

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
    OUT("Constructor");
}

ServerBlock::~ServerBlock()
{
    if (location != NULL)
    {
        delete location;
    }
    OUT("Destructor");
}

void ServerBlock::parse_listen(std::string value)
{
    (void)value;
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

}
