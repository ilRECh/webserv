#pragma once

#include "logger.hpp"
#include <string>

class Request;
class Response;

class AHeaders
{
private:
    AHeaders & operator=(AHeaders & that);

protected:
    AHeaders() : Content_length(0)
    {
        OUT_DBG("Constructor");
    }

    AHeaders(AHeaders & that)
        :   Method(that.Method),
            Path(that.Path),
            Protocol(that.Protocol),
            Host(that.Host),
            Content_type(that.Content_type),
            Content_length(that.Content_length)
    {
        OUT_DBG("Constructor");
    }

    virtual ~AHeaders()
    {
        OUT_DBG("Destructor");
    }

    std::string Method;
    std::string Path;
    std::string Protocol;
    std::string Host;
    std::string Content_type;
    size_t Content_length;

friend class Request;
friend class Response;
};
