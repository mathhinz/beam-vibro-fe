#pragma once

#include <cmath>
#include <cstdint>

namespace FEObject {
struct Bar {
  uint64_t id_ = 0;
  uint64_t matId_ = 0;
  double_t crossArea_ = 0.0;
  double_t momentInertia1 = 0.0;
  double_t momentInertia2 = 0.0;
  double_t torsionalConst = 0.0;
};

} // namespace FEObject
