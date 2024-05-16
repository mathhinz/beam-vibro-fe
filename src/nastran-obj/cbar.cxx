#include "cbar.hxx"

#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace {
auto isValidEID(uint64_t EID) -> bool {
  return ((EID == 0 || EID > 100000000) ? false : true);
}

auto isValidPID(uint64_t PID) -> bool { return (PID == 0 ? false : true); }

auto isValidG(uint64_t G) -> bool { return (G == 0 ? false : true); }

} // namespace

namespace NastranObject {
CBAR::CBAR(const uint64_t EID, const uint64_t PID, const uint64_t GA,
           const uint64_t GB, const std::array<double_t, 3> &X)
    : EID_(EID), PID_(PID), GA_(GA), GB_(GB), X_(X) {

  if (!isValidEID(EID)) {
    throw std::invalid_argument("Invalid EID input");
  }

  if (!isValidPID(EID)) {
    throw std::invalid_argument("Invalid PID input");
  }

  if (!isValidG(GA)) {
    throw std::invalid_argument("Invalid GA input");
  }
  if (!isValidG(GB)) {
    throw std::invalid_argument("Invalid GB input");
  }
};

auto CBAR::isEmpty() const -> bool { return this->EID_ == 0; }

auto CBAR::setG0(const int G0) -> void {
  assert(!this->isEmpty());
  this->G0_ = G0;
};
auto CBAR::setOFFT(const std::string OFFT) -> void {
  assert(!this->isEmpty());
  this->OFFT_ = OFFT;
};
auto CBAR::setPA(const uint64_t PA) -> void {
  assert(!this->isEmpty());
  this->PA_ = PA;
};
auto CBAR::setPB(const uint64_t PB) -> void {
  assert(!this->isEmpty());
  this->PB_ = PB;
};
auto CBAR::setWA(const std::array<double_t, 3> &WA) -> void {
  assert(!this->isEmpty());
  this->WA_ = WA;
};
auto CBAR::setWB(const std::array<double_t, 3> &WB) -> void {
  assert(!this->isEmpty());
  this->WB_ = WB;
};

auto CBAR::getEID() const -> uint64_t { return this->EID_; };
auto CBAR::getPID() const -> uint64_t { return this->PID_; };
auto CBAR::getGA() const -> uint64_t { return this->GA_; };
auto CBAR::getGB() const -> uint64_t { return this->GB_; };
auto CBAR::getX() const -> std::array<double_t, 3> { return this->X_; };
auto CBAR::getG0() const -> uint64_t { return this->G0_; };
auto CBAR::getPA() const -> uint64_t { return this->PA_; };
auto CBAR::getPB() const -> uint64_t { return this->PB_; };
auto CBAR::getWA() const -> std::array<double_t, 3> { return this->WA_; };
auto CBAR::getWB() const -> std::array<double_t, 3> { return this->WB_; };

} // namespace NastranObject
