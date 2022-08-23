#include "ABlock.hpp"
#include "Config.hpp"

void ABlock::parse_block(Config &config)
{
    while (config.good())
    {
        Parameter = config.getline_trimmed();
        
        if (not config.good())
        {
            throw ERR("Block does not end properly");
        }
        else if (Parameter == "}")
        {
            break;
        }
        
        parse_block_parameter();
        validate_parameter_value();
    }
}
