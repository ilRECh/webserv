#pragma once

#include <vector>
#include <string>

class ParsedPath
{
private:
    ParsedPath & operator=(ParsedPath & that);
    ParsedPath(ParsedPath & that);

    std::string Folder;
    std::string File;
    std::vector<std::string> Splitted_by_slash;

public:
    ParsedPath();
    ParsedPath & operator=(char * ParsedPath);
    ~ParsedPath();

    std::string const & get_folder() const;
    std::string const & get_file() const;
    std::vector<std::string> const & get_splitted_by_slash() const;
};
