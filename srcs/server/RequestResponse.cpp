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

std::string & RequestResponse::prepare(std::string & msg)
{
    std::string result;

    char * msg_parse_buf = new char[msg.size() + 1];

    strncpy(msg_parse_buf, msg.c_str(), sizeof(msg_parse_buf));

    char * method_path_protocol = std::strtok(msg_parse_buf, CRLF);

    try {
        evaluate_method_path_protocol(method_path_protocol);
        
    } catch (int error) {
        result = examine_code(error);
    } catch (...) {
        result = examine_code(404);
    }

    delete msg_parse_buf;

    return result;
}

void RequestResponse::evaluate_method_path_protocol(char * method_path_protocol)
{
    char * method   = std::strtok(method_path_protocol, " ");
    char * path     = std::strtok(NULL, CRLF);
    char * protocol = std::strtok(NULL, CRLF);

    if (method == NULL or
        path == NULL or
        protocol == NULL)
    {
        throw 400;
    }
}

std::string & RequestResponse::examine_code(int code)
{
    std::string result;

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
