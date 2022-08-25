#include "Dispatcher.hpp"
#include "ConfigFile.hpp"

void Dispatcher::read_config(std::string config_file)
{
    ConfigFile config(config_file);

    try {
        config.read_file();
    } catch (std::exception &e) {
        OUT("Catched exception: " << e.what());
        throw ERR("Config invalid");
    }

    // config.get_servers();
}

void Dispatcher::run()
{
    
}
