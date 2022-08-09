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

    CHECK_ASSERT(getaddrinfo(_Ip.c_str(), _Port.c_str(), &hints, &_ServInfo), gai_strerror(errno));

    CHECK_ASSERT(1024 > std::atoi(_Port.c_str()) || std::atoi(_Port.c_str()) > 65535, "port range [1025,65535]");

    CHECK_ASSERT((_Sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0, strerror(errno));

    CHECK_ASSERT(fcntl(_Sockfd, F_SETFL, O_NONBLOCK) < 0, strerror(errno));

	_Socklen = sizeof(sockaddr);
	
    CHECK_ASSERT(bind(_Sockfd, _ServInfo->ai_addr, _Socklen), strerror(errno));

    CHECK_ASSERT(listen(_Sockfd, SOMAXCONN), strerror(errno));

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
