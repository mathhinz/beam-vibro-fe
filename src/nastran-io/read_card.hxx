#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace NastranIO
{

struct Card
{
    std::string key;
    std::string lastLineEnd;
    std::vector < std::string > lines;
};

auto parseCards(std::ifstream &file) -> std::vector<Card>;

} // namespace NastranIO