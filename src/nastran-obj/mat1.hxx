#pragma once
#include <cmath>
#include <cstdint>

namespace NastranObject
{
// Isotropic Material

// MID      = Material identification number
// E        = Young’s modulus
// G        = Shear modulus
// NU       = Poisson’s ratio
// RHO      = Mass density
// A        = Thermal expansion coefficient
// TREF     = Reference temperature
// GE       = Structural element damping coefficient
// ST       = Stress limit for tension
// SC       = Stress limit for compression
// SS       = Stress limit for shear
// MCSID    = Material coordinate system identification number

class MAT1
{
public:
    MAT1(const uint64_t MID,
         const double_t E,
         const double_t G,
         const double_t RHO);
    MAT1()                        = default;
    MAT1(const MAT1 &)            = default;
    MAT1(MAT1 &&)                 = default;
    MAT1 &operator=(const MAT1 &) = default;
    MAT1 &operator=(MAT1 &&)      = default;
    ~MAT1()                       = default;

    auto setA(const double_t A) -> void;
    auto setTREF(const double_t TREF) -> void;
    auto setGE(const double_t GE) -> void;
    auto setST(const double_t ST) -> void;
    auto setSC(const double_t SC) -> void;
    auto setSS(const double_t SS) -> void;
    auto setMCSID(const uint64_t MCSID) -> void;

    auto getMID() const -> uint64_t;
    auto getE() const -> double_t;
    auto getG() const -> double_t;
    auto getNU() const -> double_t;
    auto getRHO() const -> double_t;
    auto getA() const -> double_t;
    auto getTREF() const -> double_t;
    auto getGE() const -> double_t;
    auto getST() const -> double_t;
    auto getSC() const -> double_t;
    auto getSS() const -> double_t;
    auto getMCSID() const -> uint64_t;

    auto isEmpty() const -> bool;

private:
    uint64_t MID_   = 0;
    double_t E_     = 0.0;
    double_t G_     = 0.0;
    double_t NU_    = 0.0;
    double_t RHO_   = 0.0;
    double_t A_     = 0.0;
    double_t TREF_  = 0.0;
    double_t GE_    = 0.0;
    double_t ST_    = 0.0;
    double_t SC_    = 0.0;
    double_t SS_    = 0.0;
    uint64_t MCSID_ = 0;
};

} // namespace NastranIO
