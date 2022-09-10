#pragma once

#include <string>
#include "AVirtualServer.hpp"

class ServerBlock;
class Request;

class VirtualServer : public AVirtualServer
{
private:
    VirtualServer();
    VirtualServer(VirtualServer & that);
    VirtualServer & operator=(VirtualServer & that);

public:
    VirtualServer(ServerBlock & block);
    virtual ~VirtualServer();

    std::string GET(Request & req);
    std::string POST(Request & req);
    std::string DELETE(Request & req);
};
