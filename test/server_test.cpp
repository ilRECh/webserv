#include "Server.hpp"

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        try {
            Server server("ilRECh serv", "localhost", argv[1]);

            while (true)
            {
                server.run();
            }
        } catch (std::exception& e) {
            OUT("Catched exception: " << e.what());
        } catch (...) {
            OUT("Unknown catched");
        }
    }
    return 0;
}
