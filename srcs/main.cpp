#include "Dispatcher.hpp"

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        try {
            Dispatcher webserv(argv[1]);
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
        OUT("Usage: ./webserv [path to config file]");
        return 1;
    }
}
