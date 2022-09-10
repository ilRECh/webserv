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

    std::map<std::string, ALocation *>::iterator location;
    std::vector<std::string>::const_reverse_iterator last = req.get_path().get_splitted_by_slash().rbegin();
    std::vector<std::string>::const_reverse_iterator first = req.get_path().get_splitted_by_slash().rend();
    std::string path;

    while (last != first)
    {
        path = req.get_path().reassemble_until(last);
        location = Locations.find(path);
        // if file or folder here
        // file -> try to open
        // folder -> index? -> Yes -> try to open; No -> autoindex?; Yes -> try to open index.html; No -> 403
        if (location)        

        ++last;
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
