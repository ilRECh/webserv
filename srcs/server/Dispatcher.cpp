#include "Dispatcher.hpp"
#include "ConfigFile.hpp"

void Dispatcher::read_config(std::string config_file)
{
    char const * err_msg = "Config invalid";
    ConfigFile config(config_file);

    try {
        config.read_file();
    } catch (std::exception &e) {
        OUT("Catched exception: " << e.what());
        throw ERR(err_msg);
    }

    Servers = config.get_servers();

    if (Servers.empty())
    {
        throw ERR(err_msg);
    }
}

void Dispatcher::run()
{
    try {
        dispatch();
    } catch (std::exception &e) {
        OUT("Catched exception: " << e.what());
        throw ERR("Failed to dispatch a Server");
    }

    while (true)
    {
        
    }
}
