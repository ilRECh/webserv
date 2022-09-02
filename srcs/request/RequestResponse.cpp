#include "RequestResponse.hpp"
#include "Server.hpp"
#include <cstring>

RequestResponse::RequestResponse(Server & srv)
    :   Server_originator(srv)
{

}

RequestResponse::~RequestResponse()
{

}

std::string RequestResponse::proceed(std::string & msg)
{
    Response resp;

    try {
        Request req(msg);
        //validate_minimal
    } catch (int error) {
        // resp = examine_code(error);
    } catch (...) {
        // resp = examine_code(404);
    }

    // return resp.string();
    return "bye";
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
