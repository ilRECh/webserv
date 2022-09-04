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

    void GET();
    void POST();
    void DELETE();

public:
    Response(Request & req);

    std::string execute();
};
