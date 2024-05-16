#include "grid.hxx"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace
{

auto isValidID(uint64_t ID) -> bool
{
    return (ID == 0 ? false : true);
}

} // namespace

namespace NastranObject
{
GRID::GRID(const uint64_t ID,
           const double_t X1,
           const double_t X2,
           const double_t X3)
    : ID_(ID), X1_(X1), X2_(X2), X3_(X3)
{
    if (!isValidID(ID))
    {
        throw std::invalid_argument("Invalid ID input");
    }
};

auto GRID::isEmpty() const -> bool
{
    return this->ID_ == 0;
}

auto GRID::setCP(const uint64_t CP) -> void
{
    assert(!this->isEmpty());
    this->CP_ = CP;
}

auto GRID::setCD(const int64_t CD) -> void
{
    assert(!this->isEmpty());
    if (CD < -1)
    {
        throw std::invalid_argument("Invalid CD input");
    }
    else
    {
        this->CD_ = CD;
    }
};

auto GRID::setPS(const uint64_t PS) -> void
{
    assert(!this->isEmpty());
    if (PS == 0 || PS > 6)
    {
        throw std::invalid_argument("Invalid PS input");
    }
    else
    {
        this->PS_ = PS;
    }
};

auto GRID::setSEID(const uint64_t SEID) -> void
{
    assert(!this->isEmpty());
    this->SEID_ = SEID;
};

auto GRID::getID() const -> uint64_t
{
    return this->ID_;
};

auto GRID::getCP() const -> uint64_t
{
    return this->CP_;
};

auto GRID::getX1() const -> double_t
{
    return this->X1_;
};

auto GRID::getX2() const -> double_t
{
    return this->X2_;
};

auto GRID::getX3() const -> double_t
{
    return this->X3_;
};

auto GRID::getCD() const -> int64_t
{
    return this->CD_;
};

auto GRID::getPS() const -> uint64_t
{
    return this->PS_;
};

auto GRID::getSEID() const -> uint64_t
{
    return this->SEID_;
};

} // namespace NastranIO
