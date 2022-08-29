#include "ServerBlock.hpp"
#include "VirtualServer.hpp"
#include "Location.hpp"
#include "Server.hpp"
#include "Connection.hpp"

Server::Server(std::string const host ,
               std::string const port ,
               std::vector<ServerBlock *> & blocks)
    :   Host(host),
        Port(port),
        Net_info(0),
        Sock_len(0),
        Fd_set(),
        Sock_fd(0),
        Max_fd(0)
{
    Virtual_servers.reserve(blocks.size());

    std::vector<ServerBlock *>::iterator block = blocks.begin();
    while (block != blocks.end())
    {
        Virtual_servers.push_back(new VirtualServer(**block));

        ++block;
    }
    OUT_DBG("Constructor");
}

Server::~Server()
{
    std::list<Connection *>::iterator conn = Accepted_conns.begin();

    while (conn != Accepted_conns.end())
    {
        delete (*conn);
        ++conn;
    }

    std::vector<VirtualServer *>::iterator virtual_server = Virtual_servers.begin();
    while (virtual_server != Virtual_servers.end())
    {
        delete (*virtual_server);
        ++virtual_server;
    }

    FD_ZERO(&Write_set);
    FD_ZERO(&Read_set);
    FD_ZERO(&Fd_set);
    freeaddrinfo(Net_info);
    close(Sock_fd);
    OUT_DBG("Free Net_info and close Sock_fd");
    OUT_DBG("Destructor");
}

void Server::init()
{
    addrinfo hints;
    memset(&hints, 0, sizeof hints);
    
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    if (1024 > std::atoi(Port.c_str()) or std::atoi(Port.c_str()) > 65535)
    {
        throw ERR("port range [1024,65535]");
    }

    if (getaddrinfo(Host.c_str(), Port.c_str(), &hints, &Net_info))
    {
        throw ERR(gai_strerror(errno));
    }

    if ((Sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        throw ERR(strerror(errno));
    }

    if (fcntl(Sock_fd, F_SETFL, O_NONBLOCK) < 0)
    {
        throw ERR(strerror(errno));
    }

    Sock_len = sizeof(sockaddr);

    if (bind(Sock_fd, Net_info->ai_addr, Sock_len))
    {
        throw ERR(strerror(errno));
    }

    if (listen(Sock_fd, SOMAXCONN))
    {
        throw ERR(strerror(errno));
    }

    OUT(   "Server Host:   " << Host << NL
        << "Server Port:   " << Port << NL
        << "Server Socket: " << Sock_fd);

    Max_fd = Sock_fd;

    FD_ZERO(&Write_set);
    FD_ZERO(&Read_set);
    FD_ZERO(&Fd_set);
    FD_SET(Sock_fd, &Fd_set);
}

void Server::run()
{
    scan_events();
    accept_incomers();
    scan_dead();
    receive();
    prepare_reply();
    reply();
}

void Server::scan_events()
{
    timeval tm = {0, 1000};
    
    Write_set = Read_set = Fd_set;
    
    if (select(Max_fd + 1, &Read_set, &Write_set, NULL, &tm) < 0)
    {
        throw ERR(strerror(errno));
    }
}

void Server::accept_incomers()
{
    if (FD_ISSET(Sock_fd, &Read_set))
    {
        int const incomer = accept(Sock_fd, Net_info->ai_addr, &Sock_len);

        if (incomer > Max_fd)
        {
            Max_fd = incomer;
        }

        fcntl(incomer, F_SETFD, O_NONBLOCK);
        Accepted_conns.push_back(new Connection(incomer));
        FD_SET(incomer, &Fd_set);
        sockaddr_in incomer_addr;
        socklen_t incomer_socklen = sizeof(incomer_addr);
        getpeername(incomer, (sockaddr *)&incomer_addr, &incomer_socklen);
        OUT("New connection: " << inet_ntoa(incomer_addr.sin_addr)
                               << ':'
                               << htons(incomer_addr.sin_port));
        FD_CLR(Sock_fd, &Read_set);
    }
}

void Server::scan_dead()
{
    char dummy = 0;
    std::list<Connection *>::iterator conn = Accepted_conns.begin();

    while (conn != Accepted_conns.end())
    {
        if (FD_ISSET((*conn)->fd, &Read_set))
        {
            const int received = recv((*conn)->fd, &dummy, sizeof(dummy), MSG_PEEK);

            if (received == 0)
            {
                FD_CLR((*conn)->fd, &Write_set);
                FD_CLR((*conn)->fd, &Read_set);
                FD_CLR((*conn)->fd, &Fd_set);
                delete (*conn);
                OUT("Connection closed: " << (*conn)->fd);
                conn = Accepted_conns.erase(conn);
            }
        }

        ++conn;
    }
}

void Server::receive()
{
    char accepted_buff[1000] = {0};
    std::list<Connection *>::iterator conn = Accepted_conns.begin();

    while (conn != Accepted_conns.end())
    {
        if (FD_ISSET((*conn)->fd, &Read_set))
        {
            FD_CLR((*conn)->fd, &Read_set);

            const int received = recv((*conn)->fd, accepted_buff, sizeof(accepted_buff) - 1, 0);

            if (received > 0)
            {
                (*conn)->accepted_msg += accepted_buff;
                OUT_DBG(Connection::log_out_with_symbols((*conn)->accepted_msg.c_str()));
                OUT("Message received from: " << (*conn)->fd);
            }
        }

        ++conn;
    }
}

void Server::prepare_reply()
{
    std::list<Connection *>::iterator conn = Accepted_conns.begin();

    while (conn != Accepted_conns.end())
    {
        if (not (*conn)->accepted_msg.empty())
        {
            // RequestResponse handler(*this);

            // if (handler->request((*conn)->accepted_msg)
            // {
            //     (*conn)->reply_msg = handler->responce();
                // (*conn)->accepted_msg.clear();
            // }
            (*conn)->reply_msg = "\nAccepted from Server: General Kenobi\n\n";
            OUT("Reply prepared for: " << (*conn)->fd);
        }

        ++conn;
    }
}

void Server::reply()
{
    std::list<Connection *>::iterator conn = Accepted_conns.begin();

    while (conn != Accepted_conns.end())
    {
        if (FD_ISSET((*conn)->fd, &Write_set))
        {
            FD_CLR((*conn)->fd, &Write_set);

            if (not (*conn)->reply_msg.empty())
            {
                send((*conn)->fd, (*conn)->reply_msg.c_str(), (*conn)->reply_msg.length(), 0);
                (*conn)->reply_msg.clear();
                OUT("Reply sent to: " << (*conn)->fd);
            }
        }

        ++conn;
    }
}
