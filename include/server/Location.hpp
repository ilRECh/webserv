#pragma once

#include "ALocation.hpp"

class LocationBlock;

class Location : public ALocation
{
private:
    Location();
    Location(Location & that);
    Location & operator=(Location & that);

public:
    Location(ALocation & block);
    virtual ~Location();

};
