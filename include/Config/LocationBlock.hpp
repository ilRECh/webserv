#pragma once

#include "ABlock.hpp"

class LocationBlock : public ABlock<LocationBlock>
{
public:
    virtual ~LocationBlock() { OUT_DBG("Destructor"); };
};
