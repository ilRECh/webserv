#include "Dispatcher.hpp"

#ifndef TESTING

int main(int argc, char **argv)
{
    char const * config_file = (argc > 1) ? argv[1] : "config/default.conf";

    try {
        Dispatcher webserv;
        webserv.read_config(config_file);
        webserv.run();
    } catch (std::exception& e) {
        OUT("Catched exception: " << e.what());
    } catch (...) {
        OUT("Unknown catched");
    }

    return 0;
}

#endif
