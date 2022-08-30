#pragma once

#include "logger.hpp"
#include <string>

class Server;

class RequestResponse
{
private:
    RequestResponse();
    RequestResponse(RequestResponse & that);
    RequestResponse & operator=(RequestResponse & that);

    Server & Server_originator;

    void evaluate_method_path_protocol(char * method_path_protocol);
    std::string & examine_code(int code);

public:
    RequestResponse(Server & srv);
    ~RequestResponse();

    std::string & prepare(std::string & msg);
};
