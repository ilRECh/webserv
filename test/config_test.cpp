#include "ConfigFile.hpp"

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        try {
            ConfigFile config(argv[1]);
            config.read_file();
        } catch (std::exception& e) {
            OUT("Catched exception: " << e.what());
        } catch (...) {
            OUT("Unknown catched");
        }
    }
    return 0;
}
