#include "barTheory.hxx"

#include <Eigen/Dense>
#include <cmath>

namespace FETheory {

auto barSlenderMassM(double_t a, double_t A, double_t rho, double_t Ix)
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

auto barSlenderStiffnessK(double_t a, double_t E, double_t v, double_t A,
                          double_t I1, double_t I2, double_t J) -> Matrix1212d {

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

auto barTimoshenkoMassM(double_t a, double_t rho, double_t A, double_t I1,
                        double_t I2, double_t J) -> Matrix1212d {

  auto const l = 2.0 * a;
  auto const l2 = std::pow(l, 2.0);
  auto const &Iz = I1;
  auto const &Iy = I2;
  auto const &Ip = J;

  auto m11 = Matrix66d::Zero().eval();
  auto m12 = Matrix66d::Zero().eval();
  auto m22 = Matrix66d::Zero().eval();

  auto m11diag = Matrix66d::Zero().eval();
  auto m11offdiag = Matrix66d::Zero().eval();

  m11diag(0, 0) = 1.0 / 3.0;
  m11diag(1, 1) = 13.0 / 35.0 + 6.0 * Iz / (5.0 * A * l2);
  m11diag(2, 2) = 13.0 / 35.0 + 6.0 * Iy / (5.0 * A * l2);
  m11diag(3, 3) = Ip / (3.0 * A);
  m11diag(4, 4) = l2 / 105.0 + 2.0 * Iy / (15.0 * A);
  m11diag(5, 5) = l2 / 105.0 + 2.0 * Iz / (15.0 * A);

  m11offdiag(1, 5) = 11.0 * l / 210.0 + Iz / (10 * A * l);
  m11offdiag(2, 4) = -11.0 * l / 210.0 - Iy / (10 * A * l);
  m11offdiag(4, 2) = m11offdiag(2, 4);
  m11offdiag(5, 1) = m11offdiag(1, 5);

  m11 = m11diag + m11offdiag;
  m22 = m11diag - m11offdiag;

  m12(0, 0) = 1.0 / 6.0;
  m12(1, 1) = 9.0 / 70.0 - 6.0 * Iz / (5.0 * A * l2);
  m12(2, 2) = 9.0 / 70.0 - 6.0 * Iy / (5.0 * A * l2);
  m12(3, 3) = Ip / (6.0 * A);
  m12(4, 4) = -l2 / 140.0 - Iy / (30.0 * A);
  m12(5, 5) = -l2 / 140.0 - Iz / (30.0 * A);
  m12(1, 5) = 13.0 * l / 420.0 - Iz / (10 * A * l);
  m12(2, 4) = -13.0 * l / 420.0 + Iy / (10 * A * l);
  m12(4, 2) = m12(2, 4);
  m12(5, 1) = -m12(1, 5);

  auto const me = rho * A * l;
  m11 *= me;
  m12 *= me;
  m22 *= me;

  auto massM = Matrix1212d::Zero().eval();

  massM.topLeftCorner(6, 6) = m11;
  massM.bottomLeftCorner(6, 6) = m12.transpose().eval();
  massM.topRightCorner(6, 6) = m12;
  massM.bottomRightCorner(6, 6) = m22;

  return massM;
}

auto barTimoshenkoStiffnessK(double_t a, double_t E, double_t G, double_t A,
                             double_t I1, double_t I2, double_t K)
    -> Matrix1212d {

  auto const l = 2.0 * a;
  auto const l2 = std::pow(l, 2.0);
  auto const l3 = std::pow(l, 3.0);
  auto const &Iz = I1;
  auto const &Iy = I2;
  auto const &It = K;
  auto const As = 5.0 / 6.0 * A;
  auto const Py = 12.0 * E * Iz / (G * As * l2);
  auto const Pz = 12.0 * E * Iy / (G * As * l2);

  auto k11 = Matrix66d::Zero().eval();
  auto k21 = Matrix66d::Zero().eval();
  auto k22 = Matrix66d::Zero().eval();

  auto k11diag = Matrix66d::Zero().eval();
  auto k11offdiag = Matrix66d::Zero().eval();

  k11diag(0, 0) = E * A / l;
  k11diag(1, 1) = 12.0 * E * Iz / (l3 * (1.0 + Py));
  k11diag(2, 2) = 12.0 * E * Iy / (l3 * (1.0 + Pz));
  k11diag(3, 3) = G * It / l;
  k11diag(4, 4) = E * Iy * (4.0 + Pz) / (l * (1.0 + Pz));
  k11diag(5, 5) = E * Iz * (4.0 + Py) / (l * (1.0 + Py));

  k11offdiag(1, 5) = 6.0 * E * Iz / (l2 * (1.0 + Py));
  k11offdiag(2, 4) = -6.0 * E * Iy / (l2 * (1.0 + Pz));
  k11offdiag(4, 2) = k11offdiag(2, 4);
  k11offdiag(5, 1) = k11offdiag(1, 5);

  k11 = k11diag + k11offdiag;
  k22 = k11diag - k11offdiag;

  k21 = -k11 + 2 * k11diag;
  k21(4, 4) = E * Iy * (2.0 - Pz) / (l * (1.0 + Pz));
  k21(5, 5) = E * Iz * (2.0 - Py) / (l * (1.0 + Py));
  k21(1, 5) = -k21(5, 1);
  k21(2, 4) = -k21(4, 2);

  auto stiffK = Matrix1212d::Zero().eval();

  stiffK.topLeftCorner(6, 6) = k11;
  stiffK.bottomLeftCorner(6, 6) = k21;
  stiffK.topRightCorner(6, 6) = k21.transpose().eval();
  stiffK.bottomRightCorner(6, 6) = k22;

  return stiffK;
}

} // namespace FETheory