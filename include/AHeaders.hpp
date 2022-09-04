#pragma once

#include <string>

class AHeaders
{
private:
    AHeaders & operator=(AHeaders & that);

protected:
    AHeaders() : Content_length(0) {}
    AHeaders(AHeaders & that)
        :   Method(that.Method),
            Path(that.Path),
            Protocol(that.Protocol),
            Host(that.Host),
            Content_type(that.Content_type),
            Content_length(that.Content_length) {}
    virtual ~AHeaders() {}

    std::string Method;
    std::string Path;
    std::string Protocol;
    std::string Host;
    std::string Content_type;
    size_t Content_length;
public:
    std::string const & get_method() const
    {
        return Method;
    }

    std::string const & get_path() const
    {
        return Path;
    }
    
    std::string const & get_protocol() const
    {
        return Protocol;
    }
    
    std::string const & get_host() const
    {
        return Host;
    }
    
    std::string const & get_content_type() const
    {
        return Content_type;
    }
    
    size_t const & get_content_length() const
    {
        return Content_length;
    }
};
