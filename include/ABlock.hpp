#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <list>
#include "logger.hpp"
#include "ConfigFile.hpp"

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
        std::mem_fun1_t<void, T, char *> callback_func;
        T * caller_object;

        friend ABlock;
    public:
        ParamCallback(const char *_param_name,
                      std::mem_fun1_t<void, T, char *> _callback,
                      T * _caller_object)
        : param_name(_param_name), callback_func(_callback), caller_object(_caller_object) {}
        
        void callback(char * arg)
        {
            callback_func(caller_object, arg);
        }
    };

    ConfigFile & Config;
    std::vector<ParamCallback> Parsers;
    
    std::list<char *> Parsing_buffers;

    void parse_and_validate_parameter(std::string parameter)
    {
        typename std::vector<ParamCallback>::iterator parser = Parsers.begin();
        while (parser != Parsers.end())
        {
            size_t size = strlen(parser->param_name);
            std::string param_name = parameter.substr(0, size);

            if (parser->param_name == param_name)
            {
                size_t start_from = size;
                parser->callback(get_parsing_buf_from(parameter.substr(start_from, parameter.length()).c_str()));
                break;
            }

            ++parser;
        }
    }

    char * get_parsing_buf_from(char const * buf)
    {
        char * new_buf = new char[std::strlen(buf) + 1];

        strcpy(new_buf, buf);
        Parsing_buffers.push_front(new_buf);
        return new_buf;
    }

    ABlock(ConfigFile & config) : Config(config) { OUT_DBG("Constructor"); };
    virtual ~ABlock()
    {
        std::list<char *>::iterator buf = Parsing_buffers.begin();
        while (buf != Parsing_buffers.end())
        {
            delete *buf;
            ++buf;
        }
        OUT_DBG("Destructor");
    };

public:

    void parse_block()
    {
        std::string line;

        while (Config.good())
        {
            line = Config.getline_trimmed();
            
            if (not Config.good())
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
