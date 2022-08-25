#pragma once

#include "logger.hpp"
#include "ConfigFile.hpp"

class Dispatcher
{
private:
    Dispatcher(Dispatcher& that);
    Dispatcher& operator=(Dispatcher& that);

    void dispatch();
public:
    Dispatcher() { OUT_DBG("Constructor"); };
    ~Dispatcher() { OUT_DBG("Destructor"); };
    void read_config(std::string config_file);
    void run();
};
