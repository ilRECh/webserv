#pragma once

//local
#include "logger.hpp"
#include <cstring>
#include <unistd.h>

class Connection
{
private:
    Connection();
    Connection(Connection& that);
    Connection& operator=(Connection& that);

    std::string accepted_msg;
    std::string reply_msg;

public:
    int const fd;

    Connection(int const fd);
    ~Connection();

    void set_accepted_msg(char const * _accepted_msg);
    std::string const & get_accepted_msg() const ;
    void set_reply_msg(std::string _reply_msg);
    std::string const & get_reply_msg() const ;
};
