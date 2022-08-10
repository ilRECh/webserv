#include "Server.hpp"

Server::Server(std::string const port)
    :   _Name("ilRECh Server"),
        _Ip("127.0.0.1"),
        _Port(port),
        _ServInfo(0),
        _Socklen(0),
        _FdSet(),
        _Sockfd(0),
        _MaxFd(0)
{
    addrinfo hints;
    memset(&hints, 0, sizeof hints);
    
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    if (getaddrinfo(_Ip.c_str(), _Port.c_str(), &hints, &_ServInfo))
    {
        throw gai_strerror(errno);
    }

    if (1024 > std::atoi(_Port.c_str()) || std::atoi(_Port.c_str()) > 65535)
    {
        throw "port range [1025,65535]";
    }

    if ((_Sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        throw strerror(errno);
    }

    if (fcntl(_Sockfd, F_SETFL, O_NONBLOCK) < 0)
    {
        throw strerror(errno);
    }

	_Socklen = sizeof(sockaddr);
	
    if (bind(_Sockfd, _ServInfo->ai_addr, _Socklen))
    {
        throw strerror(errno);
    }

    if (listen(_Sockfd, SOMAXCONN))
    {
        throw strerror(errno);
    }

    std::cout << "Server name: " << _Name << '\n'
              << "Server IP  : " << _Ip   << '\n'
              << "Server port: " << _Port << std::endl;
}

Server::~Server()
{

}

void Server::run()
{

}
