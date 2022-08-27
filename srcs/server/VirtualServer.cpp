#include "VirtualServer.hpp"
#include "ServerBlock.hpp"
#include "Location.hpp"

VirtualServer::VirtualServer(ServerBlock & block)
{
    // std::map<std::string, ALocation *>::iterator location = block.Locations.begin();
    // while (location != block.Locations.end())
    // {
    //     ALocation * new_location = new Location(*(location->second));
    //     Locations.insert(make_pair(location->first, new_location));
    
    //     ++location;
    // }
}

VirtualServer::~VirtualServer()
{

}
