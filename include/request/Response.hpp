#pragma once

#include <string>
#include <list>
#include "AHeaders.hpp"

class Request;

class Response : public AHeaders
{
private:
    std::string Method_status;
    std::list<std::string> Headers;
    std::string Body;

    std::string GET();
    std::string POST();
    std::string DELETE();

public:
    Response(Request & req);
    ~Response();

    std::string execute();
};
