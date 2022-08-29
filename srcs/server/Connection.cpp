#include "Connection.hpp"

static void replace_all(std::string &str, const char * what, const char * with)
{
    std::size_t pos = 0;

    while ((pos = str.find(what, pos)) != str.npos)
    {
        str.replace(pos, strlen(what), with);
    }
}

std::string Connection::log_out_with_symbols(char const * to_print)
{
    std::string str = to_print;

    replace_all(str, "\r", "\\r");
    replace_all(str, "\n", "\\n");

    return str;
}

Connection::Connection(const int _fd)
    :   receiving_finished(false),
        fd(_fd)
{
    OUT_DBG("Constructor");
}

Connection::~Connection()
{
    close(fd);
    OUT_DBG("Closed socket: " << fd);
    OUT_DBG("Destructor");
}
