#pragma once

#include "logger.hpp"
#include "ConfigFile.hpp"
#include <vector>

class Server;

class Dispatcher
{
private:
    Dispatcher(Dispatcher& that);
    Dispatcher& operator=(Dispatcher& that);

    std::vector<Server *> Servers;

    void dispatch();
public:
    Dispatcher();
    ~Dispatcher();
    void read_config(std::string config_file);
    void run();
};
