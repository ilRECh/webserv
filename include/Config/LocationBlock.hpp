#pragma once

#include "ABlock.hpp"
#include <set>
#include <map>

class ConfigFile;

class LocationBlock : public ABlock<LocationBlock>
{
private:
    LocationBlock(LocationBlock &that);
    LocationBlock& operator=(LocationBlock &that);

    int Autoindex;
    std::pair<int, std::string> Return; //Redirection parameter
    std::set<std::string> Allow_methods;
    std::string Root;
    std::string Index;

    void parse_allow_methods(std::string value);
    void parse_root(std::string value);
    void parse_index(std::string value);
    void parse_autoindex(std::string value);
    void parse_return(std::string value);

public:
    LocationBlock(ConfigFile & config);
    virtual void validate(); //override
    virtual ~LocationBlock() { OUT_DBG("Destructor"); }; //override
};
