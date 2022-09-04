#include "Location.hpp"
#include "LocationBlock.hpp"

Location::Location(LocationBlock & block)
    :   ALocation(block)
{
    OUT_DBG("Constructor");
}

Location::~Location()
{
    OUT_DBG("Destructor");
}
