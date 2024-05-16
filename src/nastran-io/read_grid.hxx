#pragma once
#include <grid.hxx>
#include <string>
#include <vector>

using GRID   = NastranObject::GRID;

namespace NastranIO
{

auto readGRID(std::vector<std::string> &card) -> GRID;

} // namespace NastranIO