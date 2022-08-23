#include "ServerBlock.hpp"

/**
 * @brief server block
 * 
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
