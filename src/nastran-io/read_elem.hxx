#pragma once
#include <cbar.hxx>
#include <string>
#include <vector>

using CBAR = NastranObject::CBAR;

namespace NastranIO {

auto readCBAR(std::vector<std::string> &card) -> CBAR;

} // namespace NastranIO