#pragma once

#include <string>
#include <list>
#include <vector>

class Request
{
private:
    Request();
    Request(Request & that);
    Request & operator=(Request & that);

    class ParamCallback
    {
    private:
        const char * param_name;
        std::mem_fun1_t<void, Request, char *> callback_func;
        Request * caller_object;

    public:
        ParamCallback(const char * _param_name,
                      std::mem_fun1_t<void, Request, char *> _callback,
                      Request * _caller_object)
        : param_name(_param_name), callback_func(_callback), caller_object(_caller_object) {}
        
        void callback(char * arg)
        {
            callback_func(caller_object, arg);
        }
    };

    std::vector<ParamCallback> Parsers;

    std::list<char *> Parsing_buffers;

    std::string Method;
    std::string Path;
    std::string Protocol;
    std::string Host;

    char * get_parsing_buf_from(char const * buf);
    void evaluate_method_path_protocol(char * buf);
    void parse_host(char * host);
    void parse_content_type(char * host);
    void parse_content_length(char * host);
    void validate();
    
public:
    Request(std::string & msg);
    ~Request();
};
