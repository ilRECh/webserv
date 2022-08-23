#pragma once

#include <string>
#include <fstream>

/**
 * @brief Abstrac class, Block parsing base
 * 
 */
class ABlock
{
private:
    ABlock();
    ABlock(ABlock &that);
    ABlock &operator=(ABlock &that);

protected:
    std::string Parameter;
    std::fstream &Config_file;

    void read_parameter();
    virtual void parse_parameter() = 0;
    virtual void check_parameter_value() = 0;
public:
    ABlock(std::fstream &config_file);
};
