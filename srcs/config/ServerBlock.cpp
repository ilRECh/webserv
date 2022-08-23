#include "ServerBlock.hpp"

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
const char * ServerBlock::params[] =
{
    "listen ",            //host:port
    "server_name ",       //name [name [name] ...]
    "error_page ",        //code path
    "client_body_size ",  //num
    "index ",             //path
    "location "           //location path { ... } (See below)
};
