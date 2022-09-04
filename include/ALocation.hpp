#pragma once

#include <string>
#include <set>

class Location;

class ALocation
{
private:
    ALocation & operator=(ALocation & that);

protected:
    int Autoindex;
    std::string Return; //Redirection parameter
    std::set<std::string> Allow_methods;
    std::string Root;
    std::string Index;
    std::string FastCGI_path;
    std::string Upload_pass; //URL, where the uploading starts
    std::string Upload_store; //Path, where to store uploaded files

    friend Location;

    ALocation() : Autoindex(-1) {} ;

    ALocation(ALocation & that)
        :   Autoindex(that.Autoindex),
            Return(that.Return),
            Allow_methods(that.Allow_methods),
            Root(that.Root),
            Index(that.Index),
            FastCGI_path(that.FastCGI_path),
            Upload_pass(that.Upload_pass),
            Upload_store(that.Upload_store) {}

    virtual ~ALocation() {} ;
};
