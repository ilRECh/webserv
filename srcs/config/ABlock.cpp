#include "ABlock.hpp"

ABlock::ABlock(std::fstream &config_file)
{
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
}
