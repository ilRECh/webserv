#include "ParsedPath.hpp"
#include <cstring>

ParsedPath::ParsedPath()
{

}

ParsedPath::~ParsedPath()
{

}

ParsedPath & ParsedPath::operator=(char * path)
{
    Splitted_by_slash.reserve(5);
    char * one_by_one = std::strtok(path, "/");
    while (one_by_one != NULL)
    {
        Splitted_by_slash.push_back(one_by_one);
        one_by_one = std::strtok(NULL, "/");
    }

    if (path[strlen(path) - 1] != '/')
    {
        File = *Splitted_by_slash.rbegin();
    }

    Folder = std::string(path, path + strlen(path) - Folder.length());

    return *this;
}

std::string const & ParsedPath::get_folder() const
{
    return Folder;
}

std::string const & ParsedPath::get_file() const
{
    return File;
}

std::vector<std::string> const & ParsedPath::get_splitted_by_slash() const
{
    return Splitted_by_slash;
}
    