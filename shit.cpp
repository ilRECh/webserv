#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <iostream>

int main()
{
    addrinfo *instance_net_info;
    addrinfo *server_net_info;
    addrinfo hints;
    memset(&hints, 0, sizeof hints);
    
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    getaddrinfo("127.0.0.1", "8888", &hints, &instance_net_info);
    getaddrinfo("localhost", "8888", &hints, &server_net_info);

    if (server_net_info and server_net_info->ai_addr and
        instance_net_info and instance_net_info->ai_addr)
    {
        std::cout << sizeof(server_net_info->ai_addr->sa_data) << std::endl;
        std::cout << std::boolalpha << (memcmp(server_net_info->ai_addr->sa_data,
            instance_net_info->ai_addr->sa_data,
            sizeof(server_net_info->ai_addr->sa_data)) == 0) << std::endl;
    }

    freeaddrinfo(instance_net_info);
    freeaddrinfo(server_net_info);

    return 0;
}
