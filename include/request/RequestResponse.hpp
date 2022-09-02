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

    void evaluate_method_path_protocol(char const * method_path_protocol);
    void evaluate_headers(char const * msg_parse_buf);
    Response examine_code(int code);

public:
    RequestResponse(Server & srv);
    ~RequestResponse();

    void request(std::string & msg);
    std::string & response();
};
