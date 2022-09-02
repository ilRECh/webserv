#pragma once

#include "Request.hpp"
#include "Response.hpp"
#include "logger.hpp"
#include <string>

class Server;
class Head;

class RequestResponse
{
private:
    RequestResponse();
    RequestResponse(RequestResponse & that);
    RequestResponse & operator=(RequestResponse & that);

    Server & Server_originator;

    // Response examine_code(int code);

public:
    RequestResponse(Server & srv);
    ~RequestResponse();

    std::string proceed(std::string & msg);
};
