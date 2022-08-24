#include "LocationBlock.hpp"

/**
 * @brief location block
 * allow_methods - define a list of accepted HTTP methods for the route.
 * root          - define a directory or a file from where the file should be searched
 * index         - set a default file to answer if the request is a directory.
 * autoindex     - turn on or off directory listing.
 * return        - define a HTTP redirection.
 * fastcgi_index - execute CGI based on certain file extension.
 * upload_pass   - make the route able to accept uploaded files.
 * upload_store  - configure where uploaded files should be saved.
 */
// ABlock::ParamCallback ConfigFile::setup_params[] =
// {
//     { "allow_methods " ,    //method_name [method_name [method_name]]
//     { "root "          ,    //path
//     { "index "         ,    //path
//     { "autoindex "     ,    //on/off
//     { "return "             //code uri
// };

LocationBlock::LocationBlock(ConfigFile & config)
    :   ABlock(config),
        Autoindex(-1),
        Return(std::make_pair(-1, ""))
{
    OUT_DBG("Constructor");
}

void LocationBlock::parse_allow_methods(std::string value)
{
(void) value;
}

void LocationBlock::parse_root(std::string value)
{
(void) value;
}

void LocationBlock::parse_index(std::string value)
{
(void) value;
}

void LocationBlock::parse_autoindex(std::string value)
{
(void) value;
}

void LocationBlock::parse_return(std::string value)
{
(void) value;
}

void LocationBlock::validate()
{
    if (Allow_methods.empty() or
        Root.empty()          or
        Index.empty()         or
        Autoindex == -1       or
        Return.first == -1)
    {
        throw ERR("Invalid location block");
    }
}
