#include "Server.hpp"

template <typename T, typename B>
std::string operator+(T rigth, B left)
{
    return std::string(left) + std::string(rigth);
}

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
        // receive
        // reply
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

        fcntl(incomer, F_SETFD, O_NONBLOCK);
        Accepted_fds.push_back(incomer);
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
    std::recv()

}

void Server::receive()
{

}

void Server::reply()
{

}
