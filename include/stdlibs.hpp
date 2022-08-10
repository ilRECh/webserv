#pragma once

// Outputs
#include <iostream>
#include <stdio.h>
#include <errno.h>

// STL
#include <cstring>
#include <string>
#include <sstream>
#include <list>
#include <exception>
#include <cstdlib>

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

// OUTPUT
namespace ft {
#define OUT printf("<%d><%s><%s>", __LINE__, __FILE__, __func__); printf

template <typename T>
std::string str(T arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

} // ft
