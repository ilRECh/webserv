#pragma once

#include "AVirtualServer.hpp"

class ServerBlock;

class VirtualServer : public AVirtualServer
{
private:
    VirtualServer();
    VirtualServer(VirtualServer & that);
    VirtualServer & operator=(VirtualServer & that);

public:
    VirtualServer(ServerBlock & block);
    virtual ~VirtualServer();
};
