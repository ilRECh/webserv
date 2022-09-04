#include "Response.hpp"
#include "Request.hpp"

Response::Response(Request & req)
    :   AHeaders(req)
{

}

Response::~Response()
{

}

std::string Response::execute()
{
    if (Method.empty() or
        Path.empty() or
        Protocol.empty())
    {
        throw 400;
    }

    if (Method == "GET")
    {
        if (Host.empty())
        {
            throw 400;
        }

        GET();
    }
    else if (Method == "POST")
    {
        if (Host.empty() or
            Content_type.empty() or
            Content_length == 0)
        {
            throw 400;
        }

        POST();
    }
    else if (Method == "DELETE")
    {
        DELETE();
    }
    else
    {
        throw 400;
    }
}
