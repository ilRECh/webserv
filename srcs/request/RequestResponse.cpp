#include "RequestResponse.hpp"
#include "Server.hpp"
#include <cstring>

#define CRLF "\r\n"

RequestResponse::RequestResponse(Server & srv)
    :   Server_originator(srv)
{

}

RequestResponse::~RequestResponse()
{

}

std::string & RequestResponse::request()
{
    char * msg_parse_buf = new char[msg.size() + 1];

    strncpy(msg_parse_buf, msg.c_str(), sizeof(msg_parse_buf));

    char * method_path_protocol = std::strtok(msg_parse_buf, CRLF);

    if (method_path_protocol == NULL)
    {
        throw 400;
    }

    try {
        evaluate_method_path_protocol(method_path_protocol);
        evaluate_headers(msg_parse_buf);
        //validate_minimal
    } catch (int error) {
        Resp = examine_code(error);
    } catch (...) {
        Resp = examine_code(404);
    }

    delete msg_parse_buf;
}

void RequestResponse::evaluate_method_path_protocol(char const * input_method_path_protocol)
{
    char * method_path_protocol = new char[std::strlen(input_method_path_protocol) + 1];

    std::strncpy(method_path_protocol, input_method_path_protocol, std::strlen(input_method_path_protocol) + 1);

    char * method   = std::strtok(method_path_protocol, " ");
    char * path     = std::strtok(NULL, CRLF);
    char * protocol = std::strtok(NULL, CRLF);

    if (method == NULL or
        path == NULL or
        protocol == NULL)
    {
        throw 400;
        delete method_path_protocol;
    }

    Req.method = method;
    Req.path = path;
    Req.protocol = protocol;

    delete method_path_protocol;
}

void RequestResponse::evaluate_headers(char const * msg_parse_buf)
{
    char * headers = new char[std::strlen(msg_parse_buf) + 1];

    char * header = NULL;

    while ((header = std::strtok(headers, CRLF)) != NULL)
    {

    }

    delete headers;
}

std::string response()
{

}

Response RequestResponse::examine_code(int code)
{
    Response result;

    result += "fuck you";

    switch (code)
    {
        case 301:
            result += "Redirecting";
            break;
        case 400:
            result += "Bad Request";
            break;
        case 403:
            result += "Forbidden";
            break; 
        case 404:
            result += "Not found";
            break;
        case 405:
            result += "Method not allowed";
            break;
        default:
            break;
    }

    result += "shit";

    return result;
}
