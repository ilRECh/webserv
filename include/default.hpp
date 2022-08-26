#pragma once

// AServer configuration
#define DEFAULT_HOST              "localhost"
#define DEFAULT_PORT              "8888"
#define DEFAULT_SERVER_NAMES      std::set<std::string>()
#define DEFAULT_ERROR_PAGES       std::map<int, std::string>()
#define DEFAULT_LOCATIONS         std::map<std::string, ALocation *>()
#define DEFAULT_CLIENT_BODY_SIZE  1000
