#include "Dispatcher.hpp"
#include "ConfigFile.hpp"
#include <csignal>

bool Dispatcher::Keep_alive = true;
bool Dispatcher::Signal_overrided = false;

void Dispatcher::sighandler(int)
{
    Dispatcher::Signal_overrided = false;
    Dispatcher::Keep_alive = false;
    std::signal(SIGINT, SIG_DFL);
}

void Dispatcher::signal_override()
{
    if (not Dispatcher::Signal_overrided)
    {
        if (std::signal(SIGINT, Dispatcher::sighandler) == SIG_ERR)
        {
            throw ERR("Signal override failure");
        }

        Dispatcher::Signal_overrided = true;
    }
}

Dispatcher::Dispatcher()
{
    Dispatcher::signal_override();
    OUT_DBG("Constructor");
}

Dispatcher::~Dispatcher()
{
    std::vector<Server *>::iterator server = Servers.begin();
    while (server != Servers.end())
    {
        delete (*server);
        ++server;
    }
    OUT_DBG("Destructor");
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
    while (Keep_alive)
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
