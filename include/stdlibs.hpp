#pragma once

// Outputs
#include <stdio.h>

// STL
#include <cstring>
#include <string>

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
}
