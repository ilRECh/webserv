#include "Request.hpp"
#include <cstring>
#include <algorithm>

#define CRLF "\r\n"

Request::Request(std::string & msg)
{
    Parsers.reserve(3);

    Parsers.push_back(
        Request::ParamCallback("Host: ", std::mem_fun(&Request::parse_host), this)
    );

    Parsers.push_back(
        Request::ParamCallback("Content-Type: ", std::mem_fun(&Request::parse_content_type), this)
    );

    Parsers.push_back(
        Request::ParamCallback("Content-Length: ", std::mem_fun(&Request::parse_content_length), this)
    );

    char * msg_parse_buf = get_parsing_buf_from(msg.c_str());

    evaluate_method_path_protocol(get_parsing_buf_from(std::strtok(msg_parse_buf, CRLF)));

    char * header = NULL;

    while ((header = std::strtok(NULL, CRLF)) != NULL)
    {

    }

    validate();
}

Request::~Request()
{
    std::list<char *>::iterator buf = Parsing_buffers.begin();
    while (buf != Parsing_buffers.end())
    {
        delete *buf;
        ++buf;
    }
}

char * Request::get_parsing_buf_from(char const * buf)
{
    char * new_buf = new char[std::strlen(buf) + 1];

    strncpy(new_buf, buf, sizeof(new_buf));
    Parsing_buffers.push_front(new_buf);
    return new_buf;
}

void Request::evaluate_method_path_protocol(char * method_path_protocol)
{
    char * method   = std::strtok(method_path_protocol, " ");
    char * path     = std::strtok(NULL, " ");
    char * protocol = std::strtok(NULL, " ");

    if (method == NULL or
        path == NULL or
        protocol == NULL)
    {
        throw 400;
    }

    Method = method;
    Path = path;
    Protocol = protocol;
}

void Request::parse_host(char * host)
{

}

void Request::parse_content_type(char * host)
{

}

void Request::parse_content_length(char * host)
{

}

void Request::validate()
{
    if (Method.empty() or
        Path.empty() or
        Protocol.empty() or
        Host.empty())
    {
        throw 400;
    }
}
