#pragma once
#include <cmath>
#include <cstdint>

namespace NastranObject
{

// Grid Point

// ID			= Grid point identification number
// CP			= Identification number of coordinate system
// X1, X2, X3	= Location of the grid point in coordinate system CP
// CD 			= Identification number of coordinate system
// PS			= Permanent single-point constraints
// SEID 		= Superelement identification number

class GRID
{
public:
    GRID(const uint64_t ID,
         const double_t X1,
         const double_t X2,
         const double_t X3);
    GRID()                        = default;
    GRID(const GRID &)            = default;
    GRID(GRID &&)                 = default;
    GRID &operator=(const GRID &) = default;
    GRID &operator=(GRID &&)      = default;
    ~GRID()                       = default;

    auto setCP(const uint64_t CP) -> void;
    auto setCD(const int64_t CD) -> void;
    auto setPS(const uint64_t PS) -> void;
    auto setSEID(const uint64_t SEID) -> void;

    auto getID() const -> uint64_t;
    auto getCP() const -> uint64_t;
    auto getX1() const -> double_t;
    auto getX2() const -> double_t;
    auto getX3() const -> double_t;
    auto getCD() const -> int64_t;
    auto getPS() const -> uint64_t;
    auto getSEID() const -> uint64_t;

    auto isEmpty() const -> bool;

private:
    uint64_t ID_   = 0;
    uint64_t CP_   = 0;
    double_t X1_   = 0.0;
    double_t X2_   = 0.0;
    double_t X3_   = 0.0;
    int64_t CD_    = 0;
    uint64_t PS_   = 0;
    uint64_t SEID_ = 0;
};

} // namespace NastranIO
