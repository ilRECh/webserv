#include "Server.hpp"
#include "Connection.hpp"

Server::Server(std::string const port)
    :   Name("ilRECh Server"),
        Ip("127.0.0.1"),
        Port(port),
        Net_info(0),
        Sock_len(0),
        Fd_set(),
        Sock_fd(0),
        Max_fd(0)
{
    addrinfo hints;
    memset(&hints, 0, sizeof hints);
    
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    if (getaddrinfo(Ip.c_str(), Port.c_str(), &hints, &Net_info))
    {
        throw ERR(gai_strerror(errno));
    }

    if (1024 > std::atoi(Port.c_str()) || std::atoi(Port.c_str()) > 65535)
    {
        throw ERR("port range [1025,65535]");
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

    OUT("Server name: " << Name << NL
        << "Server IP  : " << Ip   << NL
        << "Server port: " << Port << NL
        << "Server sock: " << Sock_fd);

    Max_fd = Sock_fd;

    FD_ZERO(&Fd_set);
    FD_SET(Sock_fd, &Fd_set);
}

Server::~Server()
{

}

void Server::run()
{
    while (true)
    {
        scan_events();
        accept_incomers();
        scan_dead();
        receive();
        prepare_reply();
        reply();
    }
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
        Accepted_conns.push_back(Connection(incomer));
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
    std::list<Connection>::iterator conn = Accepted_conns.begin();

    while (conn != Accepted_conns.end())
    {
        if (FD_ISSET(conn->fd, &Read_set))
        {
            const int received = recv(conn->fd, &dummy, sizeof(dummy), MSG_PEEK);

            if (received == 0)
            {
                FD_CLR(conn->fd, &Write_set);
                FD_CLR(conn->fd, &Read_set);
                FD_CLR(conn->fd, &Fd_set);
                close(conn->fd);
                OUT("Erased from all fd sets and closed connection: " << conn->fd);
                conn = Accepted_conns.erase(conn);
            }
        }

        ++conn;
    }
}

void Server::receive()
{
    char accepted_buff[1000] = {0};
    std::list<Connection>::iterator conn = Accepted_conns.begin();

    while (conn != Accepted_conns.end())
    {
        if (FD_ISSET(conn->fd, &Read_set))
        {
            FD_CLR(conn->fd, &Read_set);

            const int received = recv(conn->fd, accepted_buff, sizeof(accepted_buff) - 1, 0);

            if (received > 0)
            {
                conn->set_accepted_msg(accepted_buff);
            }
        }

        ++conn;
    }
}

void Server::prepare_reply()
{
    std::list<Connection>::iterator conn = Accepted_conns.begin();

    while (conn != Accepted_conns.end())
    {
        if (not conn->get_accepted_msg().empty())
        {
            conn->set_reply_msg("\nAccepted from Server: General Kenobi\n\n");
            conn->set_accepted_msg("");
        }

        ++conn;
    }
}

void Server::reply()
{
    std::list<Connection>::iterator conn = Accepted_conns.begin();

    while (conn != Accepted_conns.end())
    {
        if (FD_ISSET(conn->fd, &Write_set))
        {
            FD_CLR(conn->fd, &Write_set);
            if (not conn->get_reply_msg().empty())
            {
                send(conn->fd, conn->get_reply_msg().c_str(), conn->get_reply_msg().length(),0);
                conn->set_reply_msg("");
            }
        }

        ++conn;
    }
}
