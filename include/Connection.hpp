#include "stdlibs.hpp"

// stl
#include <algorithm>

class Connection
{
private:
    Connection();

    std::string accepted_msg;
    std::string reply_msg;
public:
    int const fd;

    Connection(int const fd);
    void set_accepted_msg(char const * accepted_buf);
};
