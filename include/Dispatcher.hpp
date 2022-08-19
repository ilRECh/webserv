#pragma once

#include "logger.hpp"
#include "Config.hpp"

class Dispatcher
{
private:
    Dispatcher();
    Dispatcher(Dispatcher& that);
    Dispatcher& operator=(Dispatcher& that);

    Config config;

    void dispatch();
public:
    Dispatcher(std::string const path_to_config_file);
    
    void run();

};
