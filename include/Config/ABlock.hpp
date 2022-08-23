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
        bool operator==(std::string to_compare)
        {
            return to_compare == param_name;
        }
    };

    std::string Parameter;
    std::string Value;
    std::list<ParamCallback> parsers;

    void parse_block_parameter();
    void validate_parameter_value();
public:
    ABlock(ParamCallback *first, ParamCallback *last);
    virtual ~ABlock() { OUT("Destructor"); };
    void parse_block(Config &config);
    virtual void validate() = 0;
};
