#pragma once

#include <string>
#include <list>

struct Request
{
    std::string method;
    std::string path;
    std::string protocol;
    std::list<std::string> Headers;
};
