#pragma once
#include <cmath>
#include <cstdint>

namespace NastranObject {

// Bar Element Property

// PID		          = Property identification number.
// MID		          = Material identification number.
// A 		            = Cross-section area.
// I1 	            = Area moment inertia in plane 1 about the neutral axis.
// I2	              = Area moment inertia in plane 2 about the neutral axis.
// J 	              = Torsional constant.
// NSM 		          = Nonstructural mass per unit length.
// K1, K2	          = Area factor for shear.
// Ci, Di, Ei, Fi   = Stress recovery coefficients.
// I12              = Area product of inertia.

class PBAR {
public:
  PBAR(const uint64_t PID, const uint64_t MID, const double_t A,
       const double_t I1, const double_t I2, const double_t J);
  PBAR() = default;
  PBAR(const PBAR &) = default;
  PBAR(PBAR &&) = default;
  PBAR &operator=(const PBAR &) = default;
  PBAR &operator=(PBAR &&) = default;
  ~PBAR() = default;

  auto setNSM(const double_t NSM) -> void;
  auto setK1(const double_t K1) -> void;
  auto setK2(const double_t K2) -> void;
  auto setC1(const double_t C1) -> void;
  auto setC2(const double_t C2) -> void;
  auto setD1(const double_t D1) -> void;
  auto setD2(const double_t D2) -> void;
  auto setE1(const double_t E1) -> void;
  auto setE2(const double_t E2) -> void;
  auto setF1(const double_t F1) -> void;
  auto setF2(const double_t F2) -> void;
  auto setI12(const double_t I12) -> void;

  auto getPID() const -> uint64_t;
  auto getMID() const -> uint64_t;
  auto getA() const -> double_t;
  auto getI1() const -> double_t;
  auto getI2() const -> double_t;
  auto getJ() const -> double_t;
  auto getNSM() const -> double_t;
  auto getK1() const -> double_t;
  auto getK2() const -> double_t;
  auto getC1() const -> double_t;
  auto getC2() const -> double_t;
  auto getD1() const -> double_t;
  auto getD2() const -> double_t;
  auto getE1() const -> double_t;
  auto getE2() const -> double_t;
  auto getF1() const -> double_t;
  auto getF2() const -> double_t;
  auto getI12() const -> double_t;

  auto isEmpty() const -> bool;

private:
  uint64_t PID_ = 0;
  uint64_t MID_ = 0;
  double_t A_ = 0.0;
  double_t I1_ = 0.0;
  double_t I2_ = 0.0;
  double_t J_ = 0.0;
  double_t NSM_ = 0.0;
  double_t C1_ = 0.0;
  double_t C2_ = 0.0;
  double_t D1_ = 0.0;
  double_t D2_ = 0.0;
  double_t E1_ = 0.0;
  double_t E2_ = 0.0;
  double_t F1_ = 0.0;
  double_t F2_ = 0.0;
  double_t K1_ = 0.0;
  double_t K2_ = 0.0;
  double_t I12_ = 0.0;
};

} // namespace NastranObject
