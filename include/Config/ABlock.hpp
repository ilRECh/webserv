#pragma once

#include <string>
#include <fstream>

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
    std::string Parameter;
    std::string Value;

    virtual void parse_block_parameter() = 0;
    virtual void validate_parameter_value() = 0;
public:
    virtual ~ABlock() {};
    void parse_block(Config &config);
};
