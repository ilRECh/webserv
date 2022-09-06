#include "RequestResponse.hpp"
#include "VirtualServer.hpp"
#include "Server.hpp"
#include <cstring>

RequestResponse::RequestResponse(std::vector<VirtualServer *> const & virtual_servers)
    :   Virtual_servers(virtual_servers)
{
    OUT_DBG("Constructor");
}

RequestResponse::~RequestResponse()
{
    OUT_DBG("Destructor");
}

std::string RequestResponse::proceed(std::string & msg)
{
    std::string result;

    try {
        Request req(msg, *this);
        Response resp(req);
        result = resp.execute();
    } catch (int code) {
        result = examine_code(code);
    } catch (...) {
        result = examine_code(404);
    }

    return result;
}

std::string RequestResponse::examine_code(int code)
{
    std::string head_body;

    switch (code)
    {
        case 301:
            head_body += "Redirecting";
            break;
        case 400:
            head_body += "Bad Request";
            break;
        case 403:
            head_body += "Forbidden";
            break; 
        case 404:
            head_body += "Not found";
            break;
        case 405:
            head_body += "Method not allowed";
            break;
        default:
            break;
    }

    std::string result(
        "<html>" CRLF
        "<head><title>" + head_body + "</title></head>" CRLF
        "<body>" CRLF
        "<center><h1>" + head_body + "</h1></center>" CRLF
    );

    return result;
}
