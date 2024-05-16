#pragma once

#include <cmath>
#include <cstdint>

namespace FEObject
{

struct Node
{
    uint64_t id_     = 0;
    double_t xCoord_ = 0.0;
    double_t yCoord_ = 0.0;
    double_t zCoord_ = 0.0;
};

} // namespace FEObject
