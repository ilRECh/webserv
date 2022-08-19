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

Connection::~Connection()
{
    close(fd);
    OUT("Closed socket: " << fd);
}

void Connection::set_accepted_msg(char const * _accepted_msg)
{
    log_out_with_symbols(_accepted_msg);
    accepted_msg = _accepted_msg;
}

const std::string & Connection::get_accepted_msg() const
{
    return accepted_msg;
}

void Connection::set_reply_msg(std::string _reply_msg)
{
    reply_msg = _reply_msg;
}

const std::string & Connection::get_reply_msg() const
{
    return reply_msg;
}
