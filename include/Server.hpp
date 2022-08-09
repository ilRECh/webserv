#pragma once

#include "stdlibs.hpp"

class Server {
private:
    Server();
    Server(Server& that);
    Server& operator=(Server& that);

    std::string const  _Name;
    std::string const  _Ip;
    std::string const  _Port;
    addrinfo          *_ServInfo;
    socklen_t          _Socklen;
    fd_set             _FdSet;
    int                _Sockfd;
    int                _MaxFd;
    
public:
    Server(std::string const port);
    ~Server();
    void run();
};
