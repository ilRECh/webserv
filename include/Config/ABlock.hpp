#pragma once

#include <string>
#include <fstream>
#include <list>
#include "logger.hpp"

class Config;

/**
 * @brief Abstrac class, Block parsing base
 * 
 */
class ABlock
{
private:
    ABlock(ABlock &that);
    ABlock &operator=(ABlock &that);

protected:
    struct ParamCallback
    {
        const char *param_name;
        void (*callback)();
    };

    std::string Parameter;
    std::string Value;
    std::list<std::pair<std::string, ParamCallback>> parsers;

    virtual void parse_block_parameter() = 0;
    virtual void validate_parameter_value() = 0;
public:
    virtual ~ABlock() { OUT("Destructor"); };
    void parse_block(Config &config);
    virtual void validate() = 0;
};
