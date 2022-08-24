#include "Dispatcher.hpp"

#ifndef TESTING

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        try {
            Dispatcher webserv;
            webserv.read_config(argv[1]);
            webserv.run();
        } catch (std::exception& e) {
            OUT("Catched exception: " << e.what());
        } catch (...) {
            OUT("Unknown catched");
        }
        return 0;
    }
    else
    {
        OUT("Usage: ./webserv [path to config file]");
        return 1;
    }
}

#endif
