#pragma once

#include "stdlibs.hpp"

class Server {
private:
    Server(Server& that);
    Server& operator=(Server& that);

	std::string const  _Name;
	addrinfo          *_ServInfo;
	socklen_t          _Socklen;
	fd_set             _FdsSet;
    int                _Sockfd;
	int                _MaxFd;
    
public:
    Server();
    ~Server();
    void run();
};
