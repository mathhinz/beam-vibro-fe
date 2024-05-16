#pragma once
#include <pbar.hxx>
#include <string>
#include <vector>

using PBAR = NastranObject::PBAR;

namespace NastranIO {

auto readPBAR(std::vector<std::string> &card) -> PBAR;

} // namespace NastranIO