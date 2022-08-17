#include "Connection.hpp"

static void replace_all(std::string &str, const char * what, const char * with)
{
    std::size_t pos = 0;

    while ((pos = str.find(what, pos)) != str.npos)
    {
        str.replace(pos, strlen(what), with);
    }
}

static void log_out_with_symbols(char const * to_print)
{
    std::string str = to_print;

    replace_all(str, "\r", "\\r");
    replace_all(str, "\n", "\\n");

    OUT(str);
}

Connection::Connection(const int _fd)
    :   accepted_msg(),
        fd(_fd)
{}

void Connection::set_accepted_msg(char const * accepted_buf)
{
    log_out_with_symbols(accepted_buf);
    accepted_msg = accepted_buf;
}
