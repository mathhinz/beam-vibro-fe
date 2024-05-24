#include "barTheory.hxx"

#include <Eigen/Dense>
#include <cmath>

namespace FETheory {

auto barCombinedMassM(double_t a, double_t A, double_t rho, double_t Ix)
    -> Matrix1212d {

  auto const a2 = std::pow(a, 2.0);
  auto const rx2 = Ix / A;

  auto m11 = Matrix66d::Zero().eval();
  auto m12 = Matrix66d::Zero().eval();
  auto m22 = Matrix66d::Zero().eval();

  m11(0, 0) = 70.0;
  m11(1, 1) = 78.0;
  m11(1, 5) = 22.0 * a;
  m11(2, 2) = 78.0;
  m11(2, 4) = -22.0 * a;
  m11(3, 3) = 70.0 * rx2;
  m11(4, 2) = -22.0 * a;
  m11(4, 4) = 8.0 * a2;
  m11(5, 1) = 22.0 * a;
  m11(5, 5) = 8.0 * a2;

  m12(0, 0) = 35.0;
  m12(1, 1) = 27.0;
  m12(1, 5) = -13.0 * a;
  m12(2, 2) = 27.0;
  m12(2, 4) = 13.0 * a;
  m12(3, 3) = 35.0 * rx2;
  m12(4, 2) = -13.0 * a;
  m12(4, 4) = -6.0 * a2;
  m12(5, 1) = 13.0 * a;
  m12(5, 5) = -6.0 * a2;

  m22(0, 0) = 70.0;
  m22(1, 1) = 78.0;
  m22(1, 5) = -22.0 * a;
  m22(2, 2) = 78.0;
  m22(2, 4) = 22.0 * a;
  m22(3, 3) = 70.0 * rx2;
  m22(4, 2) = 22.0 * a;
  m22(4, 4) = 8.0 * a2;
  m22(5, 1) = -22.0 * a;
  m22(5, 5) = 8.0 * a2;

  auto const coeff = rho * A * a / 105.0;
  m11 *= coeff;
  m12 *= coeff;
  m22 *= coeff;

  auto massM = Matrix1212d::Zero().eval();

  massM.topLeftCorner(6, 6) = m11;
  massM.bottomLeftCorner(6, 6) = m12.transpose().eval();
  massM.topRightCorner(6, 6) = m12;
  massM.bottomRightCorner(6, 6) = m22;

  return massM;
}

auto barCombinedStiffnessK(double_t a, double_t E, double_t v, double_t A,
                           double_t I1, double_t I2, double_t J)
    -> Matrix1212d {

  auto const a2 = std::pow(a, 2.0);
  auto const a3 = std::pow(a, 3.0);
  auto const rz2 = I1 / A;
  auto const ry2 = I2 / A;
  auto const rj2 = J / A;

  auto k11 = Matrix66d::Zero().eval();
  auto k12 = Matrix66d::Zero().eval();
  auto k22 = Matrix66d::Zero().eval();

  k11(0, 0) = 4.0 * a2;
  k11(1, 1) = 12.0 * rz2;
  k11(1, 5) = 12.0 * a * rz2;
  k11(2, 2) = 12.0 * ry2;
  k11(2, 4) = -12.0 * a * ry2;
  k11(3, 3) = 2.0 * a2 * rj2 / (1 + v);
  k11(4, 2) = -12.0 * a * ry2;
  k11(4, 4) = 16.0 * a2 * ry2;
  k11(5, 1) = 12.0 * a * rz2;
  k11(5, 5) = 16.0 * a2 * rz2;

  k12(0, 0) = -4.0 * a2;
  k12(1, 1) = -12.0 * rz2;
  k12(1, 5) = 12.0 * a * rz2;
  k12(2, 2) = -12.0 * ry2;
  k12(2, 4) = -12.0 * a * ry2;
  k12(3, 3) = -2.0 * a2 * rj2 / (1 + v);
  k12(4, 2) = 12.0 * a * ry2;
  k12(4, 4) = 8.0 * a2 * ry2;
  k12(5, 1) = -12.0 * a * rz2;
  k12(5, 5) = 8.0 * a2 * rz2;

  k22(0, 0) = 4.0 * a2;
  k22(1, 1) = 12.0 * rz2;
  k22(1, 5) = -12.0 * a * rz2;
  k22(2, 2) = 12.0 * ry2;
  k22(2, 4) = 12.0 * a * ry2;
  k22(3, 3) = 2.0 * a2 * rj2 / (1 + v);
  k22(4, 2) = 12.0 * a * ry2;
  k22(4, 4) = 16.0 * a2 * ry2;
  k22(5, 1) = -12.0 * a * rz2;
  k22(5, 5) = 16.0 * a2 * rz2;

  auto const coeff = A * E / (8.0 * a3);
  k11 *= coeff;
  k12 *= coeff;
  k22 *= coeff;

  auto stiffK = Matrix1212d::Zero().eval();

  stiffK.topLeftCorner(6, 6) = k11;
  stiffK.bottomLeftCorner(6, 6) = k12.transpose().eval();
  stiffK.topRightCorner(6, 6) = k12;
  stiffK.bottomRightCorner(6, 6) = k22;

  return stiffK;
}

} // namespace FETheory