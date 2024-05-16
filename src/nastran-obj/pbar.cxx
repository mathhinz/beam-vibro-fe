#include "pbar.hxx"

#include <cassert>
#include <stdexcept>

namespace {

auto isValidPID(uint64_t PID) -> bool { return (PID == 0 ? false : true); }

auto isValidMID(uint64_t MID) -> bool { return (MID == 0 ? false : true); }

auto isValidA(double_t A) -> bool { return (A < 0.0 ? false : true); }

auto isValidI(double_t I) -> bool { return (I < 0.0 ? false : true); }

} // namespace

namespace NastranObject {
PBAR::PBAR(const uint64_t PID, const uint64_t MID, const double_t A,
           const double_t I1, const double_t I2, const double_t J)
    : PID_(PID), MID_(MID), A_(A), I1_(I1), I2_(I2), J_(J) {

  if (!isValidPID(PID)) {
    throw std::invalid_argument("Invalid PID input");
  }

  if (!isValidMID(MID)) {
    throw std::invalid_argument("Invalid MID input");
  }

  if (!isValidA(A)) {
    throw std::invalid_argument("Invalid A input");
  }

  if (!isValidI(I1)) {
    throw std::invalid_argument("Invalid I1 input");
  }

  if (!isValidI(I2)) {
    throw std::invalid_argument("Invalid I2 input");
  }

  if (!isValidI(J)) {
    throw std::invalid_argument("Invalid J input");
  }
};

auto PBAR::isEmpty() const -> bool { return this->PID_ == 0; }

auto PBAR::setNSM(const double_t NSM) -> void {
  assert(!this->isEmpty());
  this->NSM_ = NSM;
};
auto PBAR::setK1(const double_t K1) -> void {
  assert(!this->isEmpty());
  this->K1_ = K1;
};
auto PBAR::setK2(const double_t K2) -> void {
  assert(!this->isEmpty());
  this->K2_ = K2;
};
auto PBAR::setC1(const double_t C1) -> void {
  assert(!this->isEmpty());
  this->C1_ = C1;
};
auto PBAR::setC2(const double_t C2) -> void {
  assert(!this->isEmpty());
  this->C2_ = C2;
};
auto PBAR::setD1(const double_t D1) -> void {
  assert(!this->isEmpty());
  this->D1_ = D1;
};
auto PBAR::setD2(const double_t D2) -> void {
  assert(!this->isEmpty());
  this->D2_ = D2;
};
auto PBAR::setE1(const double_t E1) -> void {
  assert(!this->isEmpty());
  this->E1_ = E1;
};
auto PBAR::setE2(const double_t E2) -> void {
  assert(!this->isEmpty());
  this->E2_ = E2;
};
auto PBAR::setF1(const double_t F1) -> void {
  assert(!this->isEmpty());
  this->F1_ = F1;
};
auto PBAR::setF2(const double_t F2) -> void {
  assert(!this->isEmpty());
  this->F2_ = F2;
};
auto PBAR::setI12(const double_t I12) -> void {
  assert(!this->isEmpty());
  if (I1_ == 0 || I2_ == 0 || I1_ * I2_ < I12) {
    throw std::invalid_argument("Invalid I12 input");
  } else {
    this->I12_ = I12;
  }
};

auto PBAR::getPID() const -> uint64_t { return this->PID_; };
auto PBAR::getMID() const -> uint64_t { return this->MID_; };
auto PBAR::getA() const -> double_t { return this->A_; };
auto PBAR::getI1() const -> double_t { return this->I1_; };
auto PBAR::getI2() const -> double_t { return this->I2_; };
auto PBAR::getJ() const -> double_t { return this->J_; };
auto PBAR::getNSM() const -> double_t { return this->NSM_; };
auto PBAR::getK1() const -> double_t { return this->K1_; };
auto PBAR::getK2() const -> double_t { return this->K2_; };
auto PBAR::getC1() const -> double_t { return this->C1_; };
auto PBAR::getC2() const -> double_t { return this->C2_; };
auto PBAR::getD1() const -> double_t { return this->D1_; };
auto PBAR::getD2() const -> double_t { return this->D2_; };
auto PBAR::getE1() const -> double_t { return this->E1_; };
auto PBAR::getE2() const -> double_t { return this->E2_; };
auto PBAR::getF1() const -> double_t { return this->F1_; };
auto PBAR::getF2() const -> double_t { return this->F2_; };
auto PBAR::getI12() const -> double_t { return this->I12_; };

} // namespace NastranObject
