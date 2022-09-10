#include "Location.hpp"
#include "LocationBlock.hpp"

Location::Location()
{
    init_default();

    OUT_DBG("Constructor");
}

Location::Location(ALocation & block)
    :   ALocation(block)
{
    init_default();

    OUT_DBG("Constructor");
}

void Location::init_default()
{
    if (Autoindex == -1)
    {
        Autoindex = true;
    }

    if (Allow_methods.empty())
    {
        Allow_methods.insert("GET");
        Allow_methods.insert("POST");
        Allow_methods.insert("DELETE");
    }

    if (Root.empty())
    {
        Root = "config/web_pages/";
    }

    if (Index.empty())
    {
        Index = "index.html";
    }
}

Location::~Location()
{
    OUT_DBG("Destructor");
}
