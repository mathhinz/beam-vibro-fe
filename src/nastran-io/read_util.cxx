#include "read_util.hxx"

#include <algorithm>
#include <cstdint>
#include <string>

namespace
{

auto trimCarriageNewline(std::string &str) -> void
{
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
}

auto padLine(std::string &line, uint64_t lineSize) -> void
{
    if (line.size() < lineSize)
    {
        line.insert(line.size(), lineSize - line.size(), ' ');
    }
}

} // namespace

namespace NastranIO
{

auto formatLine(std::string &line, uint64_t lineSize) -> void
{
    // sciNotation must be applied at conversion moment
    // otherwise it will mess with the position of the data
    trimCarriageNewline(line);
    padLine(line, lineSize);
}

}; // namespace NastranIO
