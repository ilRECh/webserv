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

    void parse_allow_methods(std::string values);
    void parse_root(std::string value);
    void parse_index(std::string value);
    void parse_autoindex(std::string value);
    void parse_return(std::string value);
    void parse_fastcgi_path(std::string value);
    void parse_upload_pass(std::string value);
    void parse_upload_store(std::string value);

public:
    LocationBlock(ConfigFile & config);
    virtual void validate(); //override
    virtual ~LocationBlock() { OUT_DBG("Destructor"); }; //override
};
