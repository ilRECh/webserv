#include "Request.hpp"
#include "VirtualServer.hpp"
#include "logger.hpp"
#include <cstring>
#include <algorithm>

Request::Request(std::string & msg,
                 std::vector<VirtualServer *> const & virtual_servers)
    :   Need_to_close(false),
        Virtual_servers(virtual_servers)
{
    Parsers.reserve(3);

    Parsers.push_back(
        Request::HeaderCallback("Host: ", std::mem_fun(&Request::parse_host), this)
    );

    Parsers.push_back(
        Request::HeaderCallback("Content-Type: ", std::mem_fun(&Request::parse_content_type), this)
    );

    Parsers.push_back(
        Request::HeaderCallback("Content-Length: ", std::mem_fun(&Request::parse_content_length), this)
    );

    char * msg_parse_buf = get_parsing_buf_from(msg.c_str());

    std::vector<char *> headers;
    headers.reserve(15);

    char * header = std::strtok(msg_parse_buf, CRLF);

    while (header != NULL)
    {
        headers.push_back(get_parsing_buf_from(header));
        header = std::strtok(NULL, CRLF);
    }

    std::vector<char *>::iterator header_iter = headers.begin();
    evaluate_method_path_protocol(*header_iter);

    while (++header_iter != headers.end())
    {
        parse_header(*header_iter);
    }

    OUT_DBG("Constructor");
}

Request::~Request()
{
    std::list<char *>::iterator buf = Parsing_buffers.begin();
    while (buf != Parsing_buffers.end())
    {
        delete *buf;
        ++buf;
    }

    OUT_DBG("Destructor");
}

char * Request::get_parsing_buf_from(char const * buf)
{
    char * new_buf = new char[std::strlen(buf) + 1];

    strcpy(new_buf, buf);
    Parsing_buffers.push_front(new_buf);
    return new_buf;
}

void Request::parse_header(char * header)
{
    std::vector<HeaderCallback>::iterator parser = Parsers.begin();
    while (parser != Parsers.end())
    {
        size_t size = strlen(parser->header_name);
        std::string header_name(header, header + (size <= strlen(header) ? size : strlen(header)));

        if (parser->header_name == header_name)
        {
            parser->callback(header);
            break;
        }

        ++parser;
    }
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
    if (Server_handler == NULL)
    {
        Host = host;

        Server_handler = *Virtual_servers.begin();

        std::vector<VirtualServer *>::const_iterator vserver = Virtual_servers.begin();
        while (vserver != Virtual_servers.end())
        {
            if ((*vserver)->get_server_names().find(host) != (*vserver)->get_server_names().end())
            {
                Server_handler = *vserver;
                break;
            }

            ++vserver;
        }
    }
}

void Request::parse_content_type(char * content_type)
{
    if (Content_type.empty())
    {
        Content_type = content_type;
    }
}

void Request::parse_content_length(char * content_length)
{
    if (Content_length == 0)
    {
        Content_length = std::atoi(content_length);
    }
}

std::string Request::execute()
{
    std::string result;

    try {
        if (Method == "GET")
        {
            result = Server_handler->GET(*this);
        }
        else if (Method == "POST")
        {
            result = Server_handler->POST(*this);
        }
        else if (Method == "DELETE")
        {
            result = Server_handler->DELETE(*this);
        }
        else
        {
            throw 400;
        }
    } catch (int err_code) {
        result = examine_err_code(err_code);
        Need_to_close = true;
    }

    return result;
}

// move to static Virtual server, rename to examine_err_code_default
// create a function, which looks for the proper error page, and if it fails,
// then the default function does its job
std::string Request::examine_err_code(int err_code)
{
    std::string head_body;

    switch (err_code)
    {
        case 301:
            head_body += "301 Redirecting";
            break;
        case 400:
            head_body += "400 Bad Request";
            break;
        case 403:
            head_body += "403 Forbidden";
            break; 
        case 404:
            head_body += "404 Not found";
            break;
        case 405:
            head_body += "405 Method not allowed";
            break;
        default:
            break;
    }

    std::string result_body(
        "<html>" CRLF
        "<head><title>" + head_body + "</title></head>" CRLF
        "<body>" CRLF
        "<center><h1>" + head_body + "</h1></center>" CRLF
        "</body>" CRLF
        "</html>" CRLF CRLF
    );

    std::string result_headers(
        "HTTP/1.1 " + head_body + CRLF
        "Connection: close" CRLF
        "Content-Type: text/html; charset=utf-8" CRLF
        "Content_length: " + ft::str(result_body.length()) + CRLF CRLF
    );

    return result_headers + result_body;
}

std::string const & Request::get_path() const
{
    return Path;
}

std::string const & Request::get_content_type() const
{
    return Content_type;
}

size_t Request::get_content_length() const
{
    return Content_length;
}
