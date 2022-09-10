#include "VirtualServer.hpp"
#include "ServerBlock.hpp"
#include "Location.hpp"
#include "LocationBlock.hpp"
#include "Request.hpp"
#include "ParsedPath.hpp"

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

    if (Locations.find("/") == Locations.end())
    {
        Locations.insert(make_pair(std::string("/"), new Location()));
    }
}

VirtualServer::~VirtualServer()
{
    
}

std::string VirtualServer::GET(Request & req)
{
    std::string result;

    if (req.get_path().get_file().empty())
    {
        std::string full_path = req.
    }

    return std::string();
}

std::string VirtualServer::POST(Request & req)
{
    (void)req;
    return std::string();
}

std::string VirtualServer::DELETE(Request & req)
{
    (void)req;
    return std::string();
}
