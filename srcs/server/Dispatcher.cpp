#include "Dispatcher.hpp"
#include "ConfigFile.hpp"

Dispatcher::Dispatcher()
{

}

Dispatcher::~Dispatcher()
{
    std::vector<Server *>::iterator server = Servers.begin();
    while (server != Servers.end())
    {
        delete (*server);
        ++server;
    }
}

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

    std::vector<Server *>::iterator server;
    while (true)
    {
        server = Servers.begin();
        while (server != Servers.end())
        {
            (*server)->run();
            ++server;
        }
    }
}

void Dispatcher::dispatch()
{
    std::vector<Server *>::iterator server = Servers.begin();
    while (server != Servers.end())
    {
        (*server)->init();
        ++server;
    }
}
