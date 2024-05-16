#pragma once

#include <line2.hxx>
#include <variant>

namespace FEModel {

using Element = std::variant<FEObject::Line2>;

} // namespace FEModel