#include "Location.hpp"
#include "LocationBlock.hpp"

Location::Location(ALocation & block)
    :   ALocation(block)
{
    OUT_DBG("Constructor");
}

Location::~Location()
{
    OUT_DBG("Destructor");
}
