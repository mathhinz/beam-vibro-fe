#pragma once
#include <mat1.hxx>
#include <string>
#include <vector>

using MAT1   = NastranObject::MAT1;

namespace NastranIO
{

auto readMAT1(std::vector<std::string> &card) -> MAT1;

} // namespace NastranIO