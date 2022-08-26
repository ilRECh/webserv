#include "Server.hpp"
#include "Connection.hpp"
#include "ServerBlock.hpp"
#include "Location.hpp"

Server::Server(std::string const host ,
               std::string const port)
    :   AServer(host, port),
        Net_info(0),
        Sock_len(0),
        Fd_set(),
        Sock_fd(0),
        Max_fd(0)
{
    OUT_DBG("Constructor");
}

Server::Server(AServer & block)
    :   AServer(block),
        Net_info(0),
        Sock_len(0),
        Fd_set(),
        Sock_fd(0),
        Max_fd(0)
{
    std::map<std::string, ALocation *>::iterator location = block.Locations.begin();
    while (location != block.Locations.end())
    {
        ALocation * new_location = new Location(*(location->second));
        Locations.insert(make_pair(location->first, new_location));

        ++location;
    }
}

Server::~Server()
{
    std::list<Connection *>::iterator conn = Accepted_conns.begin();

    while (conn != Accepted_conns.end())
    {
        delete (*conn);
        ++conn;
    }

    FD_ZERO(&Write_set);
    FD_ZERO(&Read_set);
    FD_ZERO(&Fd_set);
    freeaddrinfo(Net_info);
    close(Sock_fd);
    OUT("Free Net_info and close Sock_fd");
    OUT_DBG("Destructor");
}

void Server::init()
{
    addrinfo hints;
    memset(&hints, 0, sizeof hints);
    
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    if (getaddrinfo(Host.c_str(), Port.c_str(), &hints, &Net_info))
    {
        throw ERR(gai_strerror(errno));
    }

    if (1024 > std::atoi(Port.c_str()) or std::atoi(Port.c_str()) > 65535)
    {
        throw ERR("port range [1024,65535]");
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

    std::set<std::string>::iterator name_iter = Server_names.begin();
    while (name_iter != Server_names.end())
    {
        OUT("Server name: " << *name_iter << NL);
    }

    OUT(   "Server Host:   " << Host   << NL
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
                OUT("Erased from all fd sets: " << (*conn)->fd);
                delete (*conn);
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
                (*conn)->set_accepted_msg(accepted_buff);
                OUT("Message received");
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
        if (not (*conn)->get_accepted_msg().empty())
        {
            (*conn)->set_reply_msg("\nAccepted from Server: General Kenobi\n\n");
            (*conn)->set_accepted_msg("");
            OUT("Reply prepared");
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

            if (not (*conn)->get_reply_msg().empty())
            {
                send((*conn)->fd, (*conn)->get_reply_msg().c_str(), (*conn)->get_reply_msg().length(), 0);
                (*conn)->set_reply_msg("");
                OUT("Reply sent");
            }
        }

        ++conn;
    }
}
