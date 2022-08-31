#pragma once

#include <string>
#include <list>

struct Response
{
    std::string Method_status;
    std::list<std::string> Headers;
    std::string Body;
};
