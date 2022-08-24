#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "logger.hpp"
#include "Config.hpp"

/**
 * @brief Abstrac class, Block parsing base
 * 
 */
template<typename T>
class ABlock
{
private:
    ABlock(ABlock &that);
    ABlock &operator=(ABlock &that);

protected:
    class ParamCallback
    {
    private:
        const char *param_name;
        std::mem_fun1_t<void, T, std::string> callback_func;
        T * caller_object;

        friend ABlock;
    public:
        ParamCallback(const char *_param_name,
                      std::mem_fun1_t<void, T, std::string> _callback,
                      T * _caller_object)
        : param_name(_param_name), callback_func(_callback), caller_object(_caller_object) {}
        
        void callback(std::string arg)
        {
            callback_func(caller_object, arg);
        }
    };

    std::vector<ParamCallback> parsers;

    void parse_and_validate_parameter(std::string parameter)
    {
        typename std::vector<ParamCallback>::iterator parser = parsers.begin();
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

public:
    ABlock() { OUT_DBG("Constructor"); };
    virtual ~ABlock() { OUT_DBG("Destructor"); };

    void parse_block(Config &config)
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

    virtual void validate() = 0;
};
