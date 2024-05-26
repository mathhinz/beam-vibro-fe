#pragma once

#include <Eigen/Dense>

// Beam: Axial + Bending + Twisting
// (2010) Petyt - Introduction to Finite Element Vibration Analysis
// Pg. 84

namespace FETheory {

using Matrix66d = Eigen::Matrix<double_t, 6, 6>;
using Matrix1212d = Eigen::Matrix<double_t, 12, 12>;

auto barSlenderMassM(double_t a, double_t A, double_t rho, double_t Ix)
    -> Matrix1212d;

auto barSlenderStiffnessK(double_t a, double_t E, double_t v, double_t A,
                          double_t I1, double_t I2, double_t J) -> Matrix1212d;

auto barTimoshenkoMassM(double_t a, double_t rho, double_t A, double_t I1,
                        double_t I2, double_t J) -> Matrix1212d;

auto barTimoshenkoStiffnessK(double_t a, double_t E, double_t G, double_t A,
                             double_t I1, double_t I2, double_t K)
    -> Matrix1212d;

} // namespace FETheory
