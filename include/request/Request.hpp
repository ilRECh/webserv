#pragma once

#include <string>
#include <list>

class Request
{
private:
    Request();
    Request(Request & that);
    Request & operator=(Request & that);

    std::list<char *> Parsing_buffers;

    std::string Method;
    std::string Path;
    std::string Protocol;
    std::string Host;

    char * get_parsing_buf_from(std::string & buf);
    char * get_parsing_buf_from(char * buf);
    void evaluate_method_path_protocol(char * buf);
    void validate();
    
public:
    Request(std::string & msg);
    ~Request();
};
