#include "Config.hpp"

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
        throw ERR("Config opening error");
    }
}

Config::~Config()
{
    Config_file.close();
}

bool Config::good()
{
    return Config_file.good();
}

void Config::read_file()
{
    while (Config_file.good())
    {
        if (getline_trimmed() == "server {")
        {
            //ServerBlock *block = new ServerBlock();
            //try {
                //block.parse_block();
                //block.validate();
            // } catch (std::exception &e) {
                // delete block;
                // throw;
            // }

            //if (Instances.find() != Instances.end())
            //{
            //    Instances.insert(make_pair(block.get_host() + ":" + block.get_port(), block));
            //}
            //else
            //{
            //    delete block;
            //}
        }
    }
}

std::string Config::getline_trimmed()
{
    char const * whitespaces = "\x07\x08\x09\x0A\x0B\x0C\x0D\x20";
    std::string line;
    size_t pos = 0;

    if (Config_file.good())
    {
        std::getline(Config_file, line);

        if ((pos = line.find_first_not_of(whitespaces)) != line.npos)
        {
            line.erase(0, pos);
        }

        if ((pos = line.find_last_not_of(whitespaces)) != line.npos)
        {
            line.erase(pos + 1, line.length());
        }
    }
    else
    {
        throw ERR("Getline failed");
    }

    return line;
}
