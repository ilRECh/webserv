#pragma once

// Outputs
#include <iostream>
#include <stdio.h>
#include <errno.h>

// STL
#include <cstring>
#include <string>
#include <sstream>
#include <exception>
#include <cstdlib>
#include <ios>
#include <list>
#include <map>

// networking
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

// recv
#include <sys/types.h>
#include <sys/socket.h>

// inet_ntoa
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// OUTPUT
namespace ft {

template <typename T>
std::string str(T arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

#define OUT(OUTPUT)                        \
(std::cout << std::boolalpha               \
           << '<' << __LINE__ << "><"      \
                  << __FILE__ << "><"      \
                  << __func__ << ">\n--->" \
                  << OUTPUT << std::endl)

#define NL "\n    "

#define ERR(ERROR_MSG)                       \
(std::runtime_error(                  "<" +  \
                        ft::str(__LINE__) +  \
                                     "><" +  \
                    std::string(__FILE__) +  \
                                     "><" +  \
                    std::string(__func__) +  \
                                     "> " +  \
                                ERROR_MSG))

template<typename T>
T iterator(T iter, bool mode)
{
    static T current;

    if (mode == true)
    {
        current = iter;
        return current;
    }
    else
    {
        return current;
    }
}

// It's an iterator
#define ELEM(CONTAINER) ft::iterator(CONTAINER.begin(), false)

// hand made for_each. It is C++98, what did you expect?
#define FOR_EACH(CONTAINER, LAMBDA)                                   \
{                                                                     \
    ft::iterator(CONTAINER.begin(), true);                            \
    while (ft::iterator(CONTAINER.begin(), false) != CONTAINER.end()) \
    {                                                                 \
        LAMBDA;                                                       \
        ft::iterator(++ft::iterator(CONTAINER.begin(), false), true); \
    }                                                                 \
}


} // ft
