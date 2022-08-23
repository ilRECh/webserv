#pragma once

#include "logger.hpp"
#include "Config.hpp"

class Dispatcher
{
private:
    Dispatcher(Dispatcher& that);
    Dispatcher& operator=(Dispatcher& that);

    void dispatch();
public:
    Dispatcher();
    ~Dispatcher();
    
    void read_config(std::string config_file);
    void run();

};
