#include "mat1.hxx"
#include <cassert>
#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace
{
auto isValidMID(const uint64_t MID) -> bool
{
    return (MID == 0 ? false : true);
}

auto isValidE(const double_t E) -> bool
{
    return (E > 0.0 ? true : false);
}

auto isValidG(const double_t G) -> bool
{
    return (G > 0.0 ? true : false);
}

auto isValidNU(const double_t NU) -> bool
{
    return ((NU <= -1.0 && NU > 0.5) ? false : true);
}

} // namespace

namespace NastranObject
{

MAT1::MAT1(const uint64_t MID,
           const double_t E,
           const double_t G,
           const double_t RHO)
    : MID_(MID), E_(E), G_(G), NU_(E / (2.0 * G) - 1.0), RHO_(RHO)
{
    if (!isValidMID(MID))
    {
        throw std::invalid_argument("Invalid MID input");
    }
    if (!isValidE(E))
    {
        throw std::invalid_argument("Invalid E input");
    }
    if (!isValidG(G))
    {
        throw std::invalid_argument("Invalid G input");
    }
    if (!isValidNU(E / (2 * G) - 1))
    {
        throw std::invalid_argument("Invalid NU input");
    }
};

auto MAT1::isEmpty() const -> bool
{
    return this->MID_ == 0;
}

auto MAT1::setA(const double_t A) -> void
{
    assert(!this->isEmpty());
    this->A_ = A;
};

auto MAT1::setTREF(const double_t TREF) -> void
{
    assert(!this->isEmpty());
    this->TREF_ = TREF;
};
auto MAT1::setGE(const double_t GE) -> void
{
    assert(!this->isEmpty());
    this->GE_ = GE;
};
auto MAT1::setST(const double_t ST) -> void
{
    assert(!this->isEmpty());
    if (ST < 0.0)
    {
        throw std::invalid_argument("Invalid ST input");
    }
    else
    {
        this->ST_ = ST;
    }
};
auto MAT1::setSC(const double_t SC) -> void
{
    assert(!this->isEmpty());
    if (SC < 0.0)
    {
        throw std::invalid_argument("Invalid SC input");
    }
    else
    {
        this->SC_ = SC;
    }
};
auto MAT1::setSS(const double_t SS) -> void
{
    assert(!this->isEmpty());
    if (SS < 0.0)
    {
        throw std::invalid_argument("Invalid SS input");
    }
    else
    {
        this->SS_ = SS;
    }
};
auto MAT1::setMCSID(const uint64_t MCSID) -> void
{
    assert(!this->isEmpty());
    this->MCSID_ = MCSID;
};

auto MAT1::getMID() const -> uint64_t
{
    return this->MID_;
};
auto MAT1::getE() const -> double_t
{
    return this->E_;
};
auto MAT1::getG() const -> double_t
{
    return this->G_;
};
auto MAT1::getNU() const -> double_t
{
    return this->NU_;
};
auto MAT1::getRHO() const -> double_t
{
    return this->RHO_;
};
auto MAT1::getA() const -> double_t
{
    return this->A_;
};
auto MAT1::getTREF() const -> double_t
{
    return this->TREF_;
};
auto MAT1::getGE() const -> double_t
{
    return this->GE_;
};
auto MAT1::getST() const -> double_t
{
    return this->ST_;
};
auto MAT1::getSC() const -> double_t
{
    return this->SC_;
};
auto MAT1::getSS() const -> double_t
{
    return this->SS_;
};
auto MAT1::getMCSID() const -> uint64_t
{
    return this->MCSID_;
};

} // namespace NastranIO
