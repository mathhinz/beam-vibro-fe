#pragma once
#include <array>
#include <cmath>
#include <cstdint>
#include <string>

namespace NastranObject {

// CBAR

// EID		= Element identification number
// PID		= (Section) Property identification number
// GA 		= Grid point identification numbers A.
// GB     = Grid point identification numbers B.
// X	    = Orientation vector.
// G0     = Orientation vector using grid point 0.
// PA     = Pin flag for end A.
// PB     = Pin flag for end B.
// WA     = Offset at end A.
// WB     = Offset at end B.

class CBAR {
public:
  CBAR(const uint64_t EID, const uint64_t PID, const uint64_t GA,
       const uint64_t GB, const std::array<double_t, 3> &X);
  CBAR() = default;
  CBAR(const CBAR &) = default;
  CBAR(CBAR &&) = default;
  CBAR &operator=(const CBAR &) = default;
  CBAR &operator=(CBAR &&) = default;
  ~CBAR() = default;

  auto setG0(const int G0) -> void;
  auto setOFFT(const std::string OFFT) -> void;
  auto setPA(const uint64_t PA) -> void;
  auto setPB(const uint64_t PB) -> void;
  auto setWA(const std::array<double_t, 3> &WA) -> void;
  auto setWB(const std::array<double_t, 3> &WB) -> void;

  auto getEID() const -> uint64_t;
  auto getPID() const -> uint64_t;
  auto getGA() const -> uint64_t;
  auto getGB() const -> uint64_t;
  auto getX() const -> std::array<double_t, 3>;
  auto getG0() const -> uint64_t;
  auto getPA() const -> uint64_t;
  auto getPB() const -> uint64_t;
  auto getWA() const -> std::array<double_t, 3>;
  auto getWB() const -> std::array<double_t, 3>;

  auto isEmpty() const -> bool;

private:
  uint64_t EID_ = 0;
  uint64_t PID_ = 0;
  uint64_t GA_ = 0;
  uint64_t GB_ = 0;
  std::array<double_t, 3> X_ = {0.0, 0.0, 0.0};
  std::string OFFT_ = "GGG";
  uint64_t G0_ = 0;
  uint64_t PA_ = 0;
  uint64_t PB_ = 0;
  std::array<double_t, 3> WA_ = {0.0, 0.0, 0.0};
  std::array<double_t, 3> WB_ = {0.0, 0.0, 0.0};
};

} // namespace NastranObject
