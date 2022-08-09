#include "Server.hpp"

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        OUT("%s\n", argv[1]);
        return 0;
    }
    else
    {
        printf("\n\tUsage: ./webserv [path to config file]\n\n");
        return 1;
    }
}
