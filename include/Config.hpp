#pragma once

#include "stdlibs.hpp"
#include <fstream>

class Config
{
private:
    Config();

    int File_fd;

    void open();

public:
    Config(std::string const path_to_config_file);

};
