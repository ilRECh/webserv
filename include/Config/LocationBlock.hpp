#pragma once

#include "ABlock.hpp"

class ConfigFile;

class LocationBlock : public ABlock<LocationBlock>
{
private:
    LocationBlock(LocationBlock &that);
    LocationBlock& operator=(LocationBlock &that);

public:
    LocationBlock(ConfigFile & config);
    virtual void validate(); //override
    virtual ~LocationBlock() { OUT_DBG("Destructor"); }; //override
};
