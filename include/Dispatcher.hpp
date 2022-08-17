#pragma once

#include "stdlibs.hpp"
#include "Config.hpp"

class Dispatcher
{
private:
    Dispatcher();

    Config config;

    void dispatch();
public:
    Dispatcher(std::string const path_to_config_file);
    
    void run();

};
