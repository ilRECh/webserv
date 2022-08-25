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
        Possible_allow_methods(Possible_allow_methods_setup, Possible_allow_methods_setup + (sizeof(Possible_allow_methods_setup) / sizeof(const char *))),
        Autoindex(-1)
{
    //method_name [method_name [method_name]]
    parsers.push_back(
        ABlock::ParamCallback("allow_methods ", std::mem_fun(&LocationBlock::parse_allow_methods), this)
    );

    //path
    parsers.push_back(
        ABlock::ParamCallback("root ", std::mem_fun(&LocationBlock::parse_root), this)
    );

    //path
    parsers.push_back(
        ABlock::ParamCallback("index ", std::mem_fun(&LocationBlock::parse_index), this)
    );

    //on/off
    parsers.push_back(
        ABlock::ParamCallback("autoindex ", std::mem_fun(&LocationBlock::parse_autoindex), this)
    );

    //code uri
    parsers.push_back(
        ABlock::ParamCallback("return 301 ", std::mem_fun(&LocationBlock::parse_return), this)
    );

    //code uri
    parsers.push_back(
        ABlock::ParamCallback("fastcgi_param PATH_INFO ", std::mem_fun(&LocationBlock::parse_fastcgi_path), this)
    );

    //code uri
    parsers.push_back(
        ABlock::ParamCallback("upload_pass ", std::mem_fun(&LocationBlock::parse_upload_pass), this)
    );

    //code uri
    parsers.push_back(
        ABlock::ParamCallback("upload_store ", std::mem_fun(&LocationBlock::parse_upload_store), this)
    );

    OUT_DBG("Constructor");
}

void LocationBlock::parse_allow_methods(std::string values)
{
    if (Allow_methods.empty())
    {
        char * values_buf = new char[values.length() + 1];

        strcpy(values_buf, values.c_str());

        char * method = std::strtok(values_buf, " ");

        while (method != NULL)
        {
            if (std::find(Possible_allow_methods.begin(), Possible_allow_methods.end(), std::string(method))
                != Possible_allow_methods.end())
            {
                
                Allow_methods.insert(method);
            }

            method = std::strtok(NULL, " ");
        }

        delete values_buf;
    }
}

void LocationBlock::parse_root(std::string value)
{
    if (Root.empty())
    {
        struct stat sb;

        if (stat(value.c_str(), &sb) == 0)
        {
            if (S_ISDIR(sb.st_mode))
            {
                Root = value;
            }
        }
    }
}

void LocationBlock::parse_index(std::string value)
{
    if (Index.empty())
    {
        struct stat sb;

        if (stat(value.c_str(), &sb) == 0)
        {
            if (S_ISREG(sb.st_mode))
            {
                Index = value;
            }
        }
    }
}

void LocationBlock::parse_autoindex(std::string value)
{
    if (Autoindex == -1)
    {
        if (value == "on")
        {
            Autoindex = true;
        }
        else if (value == "off")
        {
            Autoindex = false;
        }
    }
}

void LocationBlock::parse_return(std::string value)
{
    if (Return.empty())
    {
        Return = value;
    }
}

void LocationBlock::parse_fastcgi_path(std::string value)
{
    if (FastCGI_path.empty())
    {
        struct stat sb;

        if (stat(value.c_str(), &sb) == 0)
        {
            if (S_ISREG(sb.st_mode))
            {
                FastCGI_path = value;
            }
        }
    }
}

void LocationBlock::parse_upload_pass(std::string value)
{
    if (Upload_pass.empty())
    {
        Upload_pass = value;
    }
}

void LocationBlock::parse_upload_store(std::string value)
{
    if (Upload_store.empty())
    {
        struct stat sb;

        if (stat(value.c_str(), &sb) == 0)
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
    if (Allow_methods.empty() or
        Root.empty()          or
        Index.empty()         or
        Autoindex == -1       or
        Return.empty())
    {
        throw ERR("Invalid location block");
    }
}
