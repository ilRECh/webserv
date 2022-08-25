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

    static const char * Possible_allow_methods_setup [];
    std::vector<std::string> Possible_allow_methods;

    int Autoindex;
    std::string Return; //Redirection parameter
    std::set<std::string> Allow_methods;
    std::string Root;
    std::string Index;
    std::string FastCGI_path;
    std::string Upload_pass; //URL, where the uploading starts
    std::string Upload_store; //Path, where to store uploaded files

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
