#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <sstream>

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
                  << (OUTPUT) << std::endl)

#define NL "\n    "

#define ERR(ERROR_MSG)                       \
(std::runtime_error(                  "<" +  \
                        ft::str(__LINE__) +  \
                                     "><" +  \
                    std::string(__FILE__) +  \
                                     "><" +  \
                    std::string(__func__) +  \
                                     "> " +  \
                                (ERROR_MSG)))

} // ft
