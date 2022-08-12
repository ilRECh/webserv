#include "Server.hpp"

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        try {
            Server webserv(argv[1]);
            webserv.run();
        } catch (std::exception& e) {
            OUT("Catched: " << e.what());
        } catch (...) {
            OUT("Couldn't catch");
        }
        return 0;
    }
    else
    {
        printf("\n\tUsage: ./webserv [path to config file]\n\n");
        return 1;
    }
}
