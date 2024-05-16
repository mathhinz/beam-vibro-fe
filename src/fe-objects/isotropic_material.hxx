#pragma once
#include <cmath>
#include <cstdint>

namespace FEObject
{

struct IsotropicMaterial
{
    uint64_t id_  = 0;
    double_t rho_ = 0.0;
    double_t E1_  = 0.0;
    //double_t E2_   = 0.0;
    //double_t E3_   = 0.0;
    double_t G12_ = 0.0;
    //double_t G13_  = 0.0;
    //double_t G23_  = 0.0;
    double_t nu12_ = 0.0;
    //double_t nu13_ = 0.0;
    //double_t nu23_ = 0.0;
};

} // namespace FEObject
