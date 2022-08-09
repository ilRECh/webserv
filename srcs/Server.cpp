#include "Server.hpp"

Server::Server()
{
	addrinfo hints;
	memset(&hints, 0, sizeof hints);
    
    hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags    = AI_PASSIVE;
}

Server::~Server()
{

}
