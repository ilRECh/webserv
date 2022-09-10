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
    Splitted_by_slash.reserve(21);
    char * one_by_one = std::strtok(path, "/");
    Splitted_by_slash.push_back("/");

    while (one_by_one != NULL)
    {
        Splitted_by_slash.push_back(one_by_one);
        one_by_one = std::strtok(NULL, "/");

        if (one_by_one != NULL)
        {
            *Splitted_by_slash.rbegin() += "/";
        }
    }

    if (path[strlen(path) - 1] == '/')
    {
        *Splitted_by_slash.rbegin() += "/";
    }

    return *this;
}

std::vector<std::string> const & ParsedPath::get_splitted_by_slash() const
{
    return Splitted_by_slash;
}

std::string ParsedPath::reassemble_until(std::vector<std::string>::const_reverse_iterator last) const
{
    std::string result;
    std::vector<std::string>::const_reverse_iterator first = Splitted_by_slash.rend();

    while (first != last)
    {
        result += *--first;
    }

    return result;
}
