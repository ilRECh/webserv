#pragma once

//local
#include "logger.hpp"
#include <cstring>
#include <unistd.h>

class Server;
class RequestResponse;

class Connection
{
private:
    Connection();
    Connection(Connection& that);
    Connection& operator=(Connection& that);

    std::string accepted_msg;
    std::string reply_msg;

    static std::string log_out_with_symbols(char const * to_print);

    friend class Server;
    friend class RequestResponse;
public:
    int const fd;

    Connection(int const fd);
    ~Connection();
};
