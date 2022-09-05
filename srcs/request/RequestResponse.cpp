#include "RequestResponse.hpp"
#include "Server.hpp"
#include <cstring>

RequestResponse::RequestResponse(Server & srv)
    :   Server_originator(srv)
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
        Request req(msg);
        Response resp(req);

        result = resp.execute();
    } catch (int code) {
        // result = examine_code(code);
    } catch (...) {
        // result = examine_code(404);
    }

    return result;
}

// Response RequestResponse::examine_code(int code)
// {

//     result += "fuck you";

//     switch (code)
//     {
//         case 301:
//             result += "Redirecting";
//             break;
//         case 400:
//             result += "Bad Request";
//             break;
//         case 403:
//             result += "Forbidden";
//             break; 
//         case 404:
//             result += "Not found";
//             break;
//         case 405:
//             result += "Method not allowed";
//             break;
//         default:
//             break;
//     }

//     result += "shit";

//     return result;
// }
