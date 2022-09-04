#pragma once

#include <string>
#include <list>
#include <vector>
#include "AHeaders.hpp"

class Request : public AHeaders
{
private:
    Request();
    Request(Request & that);
    Request & operator=(Request & that);

    class HeaderCallback
    {
    private:
        const char * header_name;
        std::mem_fun1_t<void, Request, char *> callback_func;
        Request * caller_object;

        friend class Request;
    public:
        HeaderCallback(const char * _header_name,
                      std::mem_fun1_t<void, Request, char *> _callback,
                      Request * _caller_object)
        : header_name(_header_name), callback_func(_callback), caller_object(_caller_object) {}
        
        void callback(char * arg)
        {
            callback_func(caller_object, arg);
        }
    };

    std::vector<HeaderCallback> Parsers;

    std::list<char *> Parsing_buffers;

    char * get_parsing_buf_from(char const * buf);
    void parse_header(std::string header);
    void evaluate_method_path_protocol(char * buf);
    void parse_host(char * host);
    void parse_content_type(char * host);
    void parse_content_length(char * host);
    
public:
    Request(std::string & msg);
    ~Request();

    void execute();
};
