#pragma once

#include <Eigen/Dense>

// Bending Vibration of Beams
// (2010) Petyt - Introduction to Finite Element Vibration Analysis

namespace FETheory {

using Matrix44d = Eigen::Matrix<double_t, 4, 4>;

auto ebBendingMassM(double_t a, double_t A, double_t rho) -> Matrix44d;

auto ebBendingStiffnessK(double_t a, double_t E, double_t Iz) -> Matrix44d;

} // namespace FETheory
