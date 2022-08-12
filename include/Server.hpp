#pragma once

#include "stdlibs.hpp"

class Server
{
private:
    Server();
    Server(Server& that);
    Server& operator=(Server& that);

    std::string const  Name;
    std::string const  Ip;
    std::string const  Port;
    addrinfo          *Net_info;
    socklen_t          Sock_len;
    fd_set             Fd_set;
    fd_set             Read_set;
    fd_set             Write_set;
    int                Sock_fd;
    int                Max_fd;

    std::list<int>     Accepted_fds;

    void scan_events();
    void accept_incomers();
    void receive();
    void reply();
    void scan_dead();

public:
    Server(std::string const port);
    ~Server();
    void run();
};
