#pragma once

#include <isotropic_material.hxx>
#include <variant>

namespace FEModel
{

using Material = std::variant<FEObject::IsotropicMaterial>;

} // namespace FEModel