#pragma once

#include <bar.hxx>
#include <variant>

namespace FEModel {

using Part = std::variant<FEObject::Bar>;

} // namespace FEModel