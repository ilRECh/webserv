#include "ABlock.hpp"
#include "Config.hpp"

ABlock::ABlock(ParamCallback *first, ParamCallback *last)
    :   parsers(first, last)
{
    OUT("Constructor");
}

void ABlock::parse_block(Config &config)
{
    std::string line;

    while (config.good())
    {
        line = config.getline_trimmed();
        
        if (not config.good())
        {
            throw ERR("Block does not end properly");
        }
        else if (line == "}")
        {
            break;
        }
        
        parse_and_validate_parameter(line);
    }
}

void ABlock::parse_and_validate_parameter(std::string parameter)
{
    std::list<ParamCallback>::iterator parser = parsers.begin();
    while (parser != parsers.end())
    {
        size_t size = strlen(parser->param_name);
        std::string param_name = parameter.substr(0, size);

        if (parser->param_name == param_name)
        {
            size_t start_from = size;
            parser->callback(parameter.substr(start_from, parameter.length()));
            break;
        }

        ++parser;
    }
}
