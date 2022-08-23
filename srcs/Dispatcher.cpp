#include "Dispatcher.hpp"
#include "Config.hpp"

void Dispatcher::read_config(std::string config_file)
{
    Config config(config_file);

    try {
        config.read_file();
    } catch (std::exception &e) {
        OUT(e.what());
        throw ERR("Config invalid");
    }

    // config.get_servers();
}
