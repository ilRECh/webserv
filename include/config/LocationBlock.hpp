#pragma once

#include "ABlock.hpp"
#include "ALocation.hpp"
#include <set>
#include <map>

class ConfigFile;

class LocationBlock : public ABlock<LocationBlock>, public ALocation
{
private:
    LocationBlock(LocationBlock &that);
    LocationBlock& operator=(LocationBlock &that);

    static const char * Possible_allow_methods_setup [];
    std::vector<std::string> Possible_allow_methods;

    void parse_allow_methods(char * values);
    void parse_root(char * value);
    void parse_index(char * value);
    void parse_autoindex(char * value);
    void parse_return(char * value);
    void parse_fastcgi_path(char * value);
    void parse_upload_pass(char * value);
    void parse_upload_store(char * value);

public:
    LocationBlock(ConfigFile & config);
    virtual ~LocationBlock(); //override
    virtual void validate(); //override
};
