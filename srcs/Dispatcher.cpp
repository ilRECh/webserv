#include "Dispatcher.hpp"
#include "Config.hpp"

Dispatcher::Dispatcher(std::string const path_to_config_file)
    :   config(path_to_config_file)
{
    OUT("Dispatcher is created");
}

void Dispatcher::run()
{

}
