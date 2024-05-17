#include "eulerBernoulli.hxx"

#include <Eigen/Dense>
#include <cmath>

namespace FETheory {

auto ebBendingMassM(double_t a, double_t A, double_t rho) -> Matrix44d {

  auto massM = Matrix44d::Zero().eval();

  auto const a2 = std::pow(a, 2.0);

  massM(0, 0) = 78.0;
  massM(0, 1) = 22.0 * a;
  massM(0, 2) = 27.0;
  massM(0, 3) = -13.0 * a;

  massM(1, 0) = 22.0 * a;
  massM(1, 1) = 8.0 * a2;
  massM(1, 2) = 13.0 * a;
  massM(1, 3) = -6.0 * a2;

  massM(2, 0) = 27.0;
  massM(2, 1) = 13.0 * a;
  massM(2, 2) = 78.0;
  massM(2, 3) = -22.0 * a;

  massM(3, 0) = -13.0 * a;
  massM(3, 1) = -6.0 * a2;
  massM(3, 2) = -22.0 * a;
  massM(3, 3) = 8.0 * a2;

  auto const coeff = rho * A * a / 105.0;
  massM *= coeff;

  return massM;
}

auto ebBendingStiffnessK(double_t a, double_t E, double_t Iz) -> Matrix44d {

  auto stiffK = Matrix44d::Zero().eval();

  auto const a2 = std::pow(a, 2.0);
  auto const a3 = std::pow(a, 3.0);

  stiffK(0, 0) = 3.0;
  stiffK(0, 1) = 3.0 * a;
  stiffK(0, 2) = -3.0;
  stiffK(0, 3) = 3.0 * a;

  stiffK(1, 0) = 3.0 * a;
  stiffK(1, 1) = 4.0 * a2;
  stiffK(1, 2) = -3.0 * a;
  stiffK(1, 3) = 2.0 * a2;

  stiffK(2, 0) = -3.0;
  stiffK(2, 1) = -3.0 * a;
  stiffK(2, 2) = 3.0;
  stiffK(2, 3) = -3.0 * a;

  stiffK(3, 0) = 3.0 * a;
  stiffK(3, 1) = 2.0 * a2;
  stiffK(3, 2) = -3.0 * a;
  stiffK(3, 3) = 4.0 * a2;

  auto const coeff = E * Iz / (2.0 * a3);
  stiffK *= coeff;

  return stiffK;
}

} // namespace FETheory