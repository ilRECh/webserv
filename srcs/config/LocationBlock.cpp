#include "LocationBlock.hpp"
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const char * LocationBlock::Possible_allow_methods_setup[] =
{
    "GET"    ,
    "POST"   ,
    "DELETE"
};

/**
 * @brief location block
 * allow_methods           - define a list of accepted HTTP methods for the route.
 * root                    - define a directory or a file from where the file should be searched
 * index                   - set a default file to answer if the request is a directory.
 * autoindex               - turn on or off directory listing.
 * return 301              - define a HTTP redirection.
 * fastcgi_param PATH_INFO - execute CGI based on certain file extension. 
 * upload_pass             - make the route able to accept uploaded files.
 * upload_store            - configure where uploaded files should be saved.
 */
LocationBlock::LocationBlock(ConfigFile & config)
    :   ABlock(config),
        ALocation(),
        Possible_allow_methods(Possible_allow_methods_setup, Possible_allow_methods_setup + (sizeof(Possible_allow_methods_setup) / sizeof(const char *)))
{
    Parsers.reserve(8);

    //method_name [method_name [method_name]]
    Parsers.push_back(
        ABlock::ParamCallback("allow_methods ", std::mem_fun(&LocationBlock::parse_allow_methods), this)
    );

    //path
    Parsers.push_back(
        ABlock::ParamCallback("root ", std::mem_fun(&LocationBlock::parse_root), this)
    );

    //path
    Parsers.push_back(
        ABlock::ParamCallback("index ", std::mem_fun(&LocationBlock::parse_index), this)
    );

    //on/off
    Parsers.push_back(
        ABlock::ParamCallback("autoindex ", std::mem_fun(&LocationBlock::parse_autoindex), this)
    );

    //code uri
    Parsers.push_back(
        ABlock::ParamCallback("return 301 ", std::mem_fun(&LocationBlock::parse_return), this)
    );

    //code uri
    Parsers.push_back(
        ABlock::ParamCallback("fastcgi_param PATH_INFO ", std::mem_fun(&LocationBlock::parse_fastcgi_path), this)
    );

    //code uri
    Parsers.push_back(
        ABlock::ParamCallback("upload_pass ", std::mem_fun(&LocationBlock::parse_upload_pass), this)
    );

    //code uri
    Parsers.push_back(
        ABlock::ParamCallback("upload_store ", std::mem_fun(&LocationBlock::parse_upload_store), this)
    );

    OUT_DBG("Constructor");
}

LocationBlock::~LocationBlock()
{
    OUT_DBG("Destructor");
}

void LocationBlock::parse_allow_methods(char * values)
{
    if (Allow_methods.empty())
    {
        char * method = std::strtok(values, " ");

        while (method != NULL)
        {
            if (std::find(Possible_allow_methods.begin(), Possible_allow_methods.end(), std::string(method))
                != Possible_allow_methods.end())
            {
                
                Allow_methods.insert(method);
            }

            method = std::strtok(NULL, " ");
        }
    }
}

void LocationBlock::parse_root(char * value)
{
    if (Root.empty())
    {
        struct stat sb;

        if (stat(value, &sb) == 0)
        {
            if (S_ISDIR(sb.st_mode))
            {
                Root = value;
            }
        }
    }
}

void LocationBlock::parse_index(char * value)
{
    if (Index.empty())
    {
        struct stat sb;

        if (stat(value, &sb) == 0)
        {
            if (S_ISREG(sb.st_mode))
            {
                Index = value;
            }
        }
    }
}

void LocationBlock::parse_autoindex(char * value)
{
    if (Autoindex == -1)
    {
        if (std::strcmp(value, "on"))
        {
            Autoindex = true;
        }
        else if (std::strcmp(value, "off"))
        {
            Autoindex = false;
        }
    }
}

void LocationBlock::parse_return(char * value)
{
    if (Return.empty())
    {
        Return = value;
    }
}

void LocationBlock::parse_fastcgi_path(char * value)
{
    if (FastCGI_path.empty())
    {
        struct stat sb;

        if (stat(value, &sb) == 0)
        {
            if (S_ISREG(sb.st_mode))
            {
                FastCGI_path = value;
            }
        }
    }
}

void LocationBlock::parse_upload_pass(char * value)
{
    if (Upload_pass.empty())
    {
        Upload_pass = value;
    }
}

void LocationBlock::parse_upload_store(char * value)
{
    if (Upload_store.empty())
    {
        struct stat sb;

        if (stat(value, &sb) == 0)
        {
            if (S_ISDIR(sb.st_mode))
            {
                Upload_store = value;
            }
        }
    }
}

void LocationBlock::validate()
{
    if (Allow_methods.empty() and
        Root.empty()          and
        Index.empty()         and
        Autoindex == -1       and
        Return.empty()        and
        FastCGI_path.empty()  and
        Upload_pass.empty()   and
        Upload_store.empty())
    {
        throw ERR("Invalid location block");
    }
}
