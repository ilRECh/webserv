#pragma once

#include "ABlock.hpp"
#include <map>

class ConfigFile;

class LocationBlock : public ABlock<LocationBlock>
{
private:
    LocationBlock(LocationBlock &that);
    LocationBlock& operator=(LocationBlock &that);

    std::set<std::string> Method_names;
    std::string Root;
    std::string Index;
    bool Autoindex;
    std::pair<int, std::string> Return; //Redirection parameter

    void parse_method_names();
    void parse_root();
    void parse_index();
    void parse_autoindex();
    void parse_return();

public:
    LocationBlock(ConfigFile & config);
    virtual void validate(); //override
    virtual ~LocationBlock() { OUT_DBG("Destructor"); }; //override
};
