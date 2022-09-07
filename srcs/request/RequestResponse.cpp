#include "RequestResponse.hpp"
#include "VirtualServer.hpp"
#include "Connection.hpp"
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

std::string RequestResponse::proceed(std::string & msg, Connection & conn)
{
    std::string result;

    try {
        Request req(msg, *this);
        Response resp(req);
        result = resp.execute();
    } catch (int code) {
        result = examine_code(code);
        conn.need_to_close();
    } catch (...) {
        result = examine_code(404);
        conn.need_to_close();
    }

    return result;
}

std::string RequestResponse::examine_code(int code)
{
    std::string head_body;

    switch (code)
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
