#pragma once

#include <vector>
#include <string>

class ParsedPath
{
private:
    ParsedPath & operator=(ParsedPath & that);
    ParsedPath(ParsedPath & that);

    std::vector<std::string> Splitted_by_slash;

public:
    ParsedPath();
    ParsedPath & operator=(char * ParsedPath);
    ~ParsedPath();

    std::vector<std::string> const & get_splitted_by_slash() const;
    std::string reassemble_until(std::vector<std::string>::const_reverse_iterator last) const;
};
