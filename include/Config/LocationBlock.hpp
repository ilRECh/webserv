#pragma once

#include "ABlock.hpp"

class LocationBlock : public ABlock
{
public:
    virtual ~LocationBlock() { OUT("Destructor"); };
};
