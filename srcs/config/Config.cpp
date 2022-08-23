#include "Config.hpp"

static void trim(std::string &to_trim)
{
    char const * whitespaces = "\x07\x08\x09\x0A\x0B\x0C\x0D\x20";
    size_t pos = 0;

    if ((pos = to_trim.find_first_not_of(whitespaces)) != to_trim.npos)
    {
        to_trim.erase(0, pos);
    }

    if ((pos = to_trim.find_last_not_of(whitespaces)) != to_trim.npos)
    {
        to_trim.erase(pos + 1, to_trim.length());
    }
}

static void getline_trimmed(std::ifstream &input, std::string &line)
{
    std::getline(input, line);
    trim(line);
}

/**
 * @brief server block
 * 
 * 
 */
const char * Config::server_params[] =
{
    "listen ",            //host:port
    "server_name ",       //name [name [name] ...]
    "error_page ",        //code path
    "client_body_size ",  //num
    "index ",             //path
    "location "           //location path { ... } (See below)
};

/**
 * @brief location block
 * allow_methods - define a list of accepted HTTP methods for the route.
 * root          - define a directory or a file from where the file should be searched
 * index         - set a default file to answer if the request is a directory.
 * autoindex     - turn on or off directory listing.
 * return        - define a HTTP redirection.
 * fastcgi_index - execute CGI based on certain file extension.
 * upload_pass   - make the route able to accept uploaded files.
 * upload_store  - configure where uploaded files should be saved.
 */
const char * Config::location_params[] =
{
    "allow_methods " ,    //method_name [method_name [method_name]]
    "root "          ,    //path
    "index "         ,    //path
    "autoindex "     ,    //on/off
    "return "             //code uri
};

Config::Config(std::string const path_to_config_file)
    :   Config_file(path_to_config_file.c_str())
{
    if (Config_file.fail())
    {
        throw ERR("Config invalid");
    }

    try {
        read_file();
    } catch (...) {
        Instances.clear();
    }

    Config_file.close();

    if (Instances.empty())
    {
        throw ERR("Config invalid");
    }
}

void Config::read_file()
{
    std::string line;

    while (Config_file.good())
    {
        getline_trimmed(Config_file, line);

        if (line == "server {")
        {
            
        }
    }
}

void Config::parse_server_instance()
{
    ServerInstance tmp_server_instace;
    std::string line;

    while (Config_file.good())
    {
        getline_trimmed(Config_file, line);
        parse_server_instance_parameter(tmp_server_instace, line);

        if (Config_file.good() and line == "}")
        {
            break;
        }
        else if (Config_file.bad())
        {
            throw ERR("");
        }
    }

    // if (examine_server_instance(tmp_server_instace))
    // {
    //     add_server_instance(tmp_server_instace);
    // }
    // else
    // {
    //     throw ERR("");
    // }

}

void Config::parse_server_instance_parameter(ServerInstance &instance,
                                             std::string &parameter)
{
    (void)instance;
    (void)parameter;
}

