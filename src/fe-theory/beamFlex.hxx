#pragma once

#include <Eigen/Dense>

#include <bar.hxx>
#include <cmath>
#include <isotropic_material.hxx>
#include <line2.hxx>
#include <model.hxx>
#include <node.hxx>
#include <unordered_map>

namespace FETheory {

using Matrix44d = Eigen::Matrix<double_t, 4, 4>;
using Vector3d = Eigen::Vector<double_t, 3>;
using Vector4u64 = Eigen::Vector<uint64_t, 4>;

struct ebBarParameters {
  double_t density = 0.0;
  double_t youngE = 0.0;
  double_t momentIz = 0.0;
  double_t crossA = 0.0;

  Vector4u64 dofsIdx = Vector4u64{0, 1, 2, 3};
};

auto getEuBeBarParameters(FEModel::System const &system,
                          FEObject::Bar const &bar) -> ebBarParameters;

struct EulerBernoulliBar {
  double_t mass = 0.0;
  Matrix44d localK = Matrix44d::Zero().eval();
  Matrix44d localM = Matrix44d::Zero().eval();
  Vector4u64 dofsIdx = Vector4u64::Zero().eval();
};

auto getBendingBeamLocalKandM(
    FEObject::Line2 const &ele2,
    std::unordered_map<uint64_t, FEObject::Node> const &nodes,
    FEObject::Bar const &bar, ebBarParameters const &ebParam)
    -> EulerBernoulliBar;

} // namespace FETheory
