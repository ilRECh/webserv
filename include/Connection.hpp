#pragma once

//local
#include "stdlibs.hpp"

class Connection
{
private:
    Connection();

    std::string accepted_msg;
    std::string reply_msg;
public:
    int const fd;

    Connection(int const fd);

    void set_accepted_msg(char const * _accepted_msg);
    std::string const & get_accepted_msg() const ;
    void set_reply_msg(std::string _reply_msg);
    std::string const & get_reply_msg() const ;
};
