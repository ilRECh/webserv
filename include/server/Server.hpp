#pragma once

#include "logger.hpp"
#include "AVirtualServer.hpp"

#include <errno.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <list>

// networking
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

// recv
#include <sys/types.h>
#include <sys/socket.h>

// inet_ntoa
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Connection;
class VirtualServer;

class Server
{
private:
    Server();
    Server(Server& that);
    Server& operator=(Server& that);

    std::string  Host;
    std::string  Port;
    addrinfo    *Net_info;
    socklen_t    Sock_len;
    fd_set       Fd_set;
    fd_set       Read_set;
    fd_set       Write_set;
    int          Sock_fd;
    int          Max_fd;

    std::vector<VirtualServer *> Virtual_servers;

    std::list<Connection *> Accepted_conns;

    void scan_events();
    void accept_incomers();
    void receive();
    void prepare_reply();
    void reply();
    void scan_dead();

public:
    Server(std::string const host ,
           std::string const port ,
           std::vector<ServerBlock *> & blocks);
    ~Server();
    void init();
    void run();
};
