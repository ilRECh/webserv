#pragma once

#include "ALocation.hpp"

class LocationBlock;

class Location : public ALocation
{
private:
    Location(Location & that);
    Location & operator=(Location & that);

    void init_default();

public:
    Location();
    Location(ALocation & block);
    virtual ~Location();

};
