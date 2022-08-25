#pragma once

#include <string>
#include <set>

class ALocation
{
protected:
    int Autoindex;
    std::string Return; //Redirection parameter
    std::set<std::string> Allow_methods;
    std::string Root;
    std::string Index;
    std::string FastCGI_path;
    std::string Upload_pass; //URL, where the uploading starts
    std::string Upload_store; //Path, where to store uploaded files
public:
    ALocation() : Autoindex(-1) {} ;
    virtual ~ALocation() {} ;
};
