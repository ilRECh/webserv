#include "Dispatcher.hpp"
#include "Config.hpp"

Dispatcher::Dispatcher()
{
    OUT("Done");
}

Dispatcher::~Dispatcher()
{
    OUT("Done");
}

void Dispatcher::read_config(std::string config_file)
{
    Config config(config_file);

    try {
        config.read_file();
    } catch (std::exception &e) {
        throw;
    }
}
