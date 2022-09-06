#pragma once

#include "Request.hpp"
#include "Response.hpp"
#include "logger.hpp"
#include <vector>
#include <string>

class VirtualServer;

class RequestResponse
{
private:
    RequestResponse();
    RequestResponse(RequestResponse & that);
    RequestResponse & operator=(RequestResponse & that);

    std::vector<VirtualServer *> const & Virtual_servers;

    std::string examine_code(int code);

    friend class Request;

public:
    RequestResponse(std::vector<VirtualServer *> const & virtual_servers);
    ~RequestResponse();

    std::string proceed(std::string & msg);
};
