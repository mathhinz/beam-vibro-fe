#pragma once

#include <array>
#include <cstdint>

namespace FEObject {

struct Line2 {
  uint64_t id_ = 0;
  uint64_t partId_ = 0;
  std::array<uint64_t, 2> nodesId_ = {0, 0};
  std::array<double_t, 3> direction_ = {0.0, 0.0, 0.0};
};

} // namespace FEObject
