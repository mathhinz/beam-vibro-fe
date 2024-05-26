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

using Matrix1212d = Eigen::Matrix<double_t, 12, 12>;
using Matrix33d = Eigen::Matrix<double_t, 3, 3>;
using Vector3d = Eigen::Vector<double_t, 3>;
using Vector12u64 = Eigen::Vector<uint64_t, 12>;

struct BarSectionParameters {
  double_t density = 0.0;
  double_t youngE = 0.0;
  double_t shearG = 0.0;
  double_t sectionA = 0.0;
  double_t momentI1 = 0.0;
  double_t momentI2 = 0.0;
  double_t momentJ = 0.0;
  double_t torsionK = 0.0;

  Vector12u64 dofsFlexIdx = Vector12u64{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
};

auto getBarSectionParameters(FEModel::System const &system,
                             FEObject::Bar const &bar) -> BarSectionParameters;

struct Bar3D {
  Matrix1212d localK = Matrix1212d::Zero().eval();
  Matrix1212d localM = Matrix1212d::Zero().eval();
  Matrix1212d transR = Matrix1212d::Identity().eval();
  Vector12u64 dofsIdx = Vector12u64::Zero().eval();
};

auto getBar3DLocalKandM(
    FEObject::Line2 const &ele2,
    std::unordered_map<uint64_t, FEObject::Node> const &nodes,
    FEObject::Bar const &bar, BarSectionParameters const &barSec) -> Bar3D;

} // namespace FETheory
