#include "Response.hpp"
#include "Request.hpp"
#include "logger.hpp"

Response::Response(Request & req)
    :   AHeaders(req)
{
    OUT_DBG("Constructor");
}

Response::~Response()
{
    OUT_DBG("Destructor");
}

std::string Response::execute()
{
    if (Method.empty() or
        Path.empty() or
        Protocol.empty())
    {
        throw 400;
    }

    std::string result;

    if (Method == "GET")
    {
        if (Host.empty())
        {
            throw 400;
        }

        result = GET();
    }
    else if (Method == "POST")
    {
        if (Host.empty() or
            Content_type.empty() or
            Content_length == 0)
        {
            throw 400;
        }

        result = POST();
    }
    else if (Method == "DELETE")
    {
        result = DELETE();
    }
    else
    {
        throw 400;
    }

    return result;
}

std::string Response::GET()
{
    std::string result;

    return result;
}

std::string Response::POST()
{
    std::string result;

    return result;
}

std::string Response::DELETE()
{
    std::string result;

    return result;
}
