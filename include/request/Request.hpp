#pragma once

#include <string>
#include <list>
#include <vector>
#include "ParsedPath.hpp"

class VirtualServer;

class Request
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

    bool Need_to_close;

    std::string Method;
    ParsedPath Path;
    std::string Protocol;
    std::string Host;
    VirtualServer * Server_handler;
    std::string Content_type;
    size_t Content_length;

    std::vector<HeaderCallback> Parsers;
    std::list<char *> Parsing_buffers;
    std::vector<VirtualServer *> const & Virtual_servers;

    char * get_parsing_buf_from(char const * buf);
    void parse_header(char * header);
    void evaluate_method_path_protocol(char * buf);
    void parse_host(char * host);
    void parse_content_type(char * host);
    void parse_content_length(char * host);
    std::string examine_err_code(int err_code);

public:
    Request(std::string & msg,
            std::vector<VirtualServer *> const & virtual_servers);
    ~Request();

    ParsedPath const & get_path() const;
    std::string const & get_content_type() const;
    size_t get_content_length() const;

    std::string execute();
};
