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

void RequestResponse::request(std::string & msg)
{


    try {
        Request req(msg);
        //validate_minimal
    } catch (int error) {
        Resp = examine_code(error);
    } catch (...) {
        Resp = examine_code(404);
    }


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
