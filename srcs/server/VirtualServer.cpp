#include "VirtualServer.hpp"
#include "ServerBlock.hpp"
#include "Location.hpp"
#include "LocationBlock.hpp"

VirtualServer::VirtualServer(ServerBlock & block)
    :   AVirtualServer(block)
{
    std::map<std::string, ALocation *>::const_iterator location = block.get_locations().begin();
    while (location != block.get_locations().end())
    {
        ALocation * new_location = new Location(*(location->second));

        Locations.insert(make_pair(location->first, new_location));
    
        ++location;
    }
}

VirtualServer::~VirtualServer()
{
    
}
