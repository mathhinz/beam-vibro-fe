#include "beamFlex.hxx"

#include <Eigen/Dense>
#include <bar.hxx>
#include <eulerBernoulli.hxx>
#include <isotropic_material.hxx>
#include <line2.hxx>
#include <model.hxx>
#include <node.hxx>
#include <unordered_map>
#include <variant>

namespace FETheory {

auto getEuBeBarParameters(FEModel::System const &system,
                          FEObject::Bar const &bar) -> ebBarParameters {

  // NOTE: Nastran input is generic as per necessary for the other formulations
  // This element formulation oversimplifies/ignores a lot of the inputs

  // Result
  auto properties = ebBarParameters{};

  // (Material)
  auto const &mat = system.materials_.at(bar.matId_);
  if (std::holds_alternative<FEObject::IsotropicMaterial>(mat)) {
    auto const &isoMemb = std::get<FEObject::IsotropicMaterial>(mat);
    properties.density = isoMemb.rho_;
    properties.youngE = isoMemb.E1_;
  }

  // (Geometry)
  properties.momentIz = bar.momentInertiaX + bar.momentInertiaY;
  properties.crossA = bar.crossArea_;

  return properties;
}

auto getBendingBeamLocalKandM(
    FEObject::Line2 const &ele2,
    std::unordered_map<uint64_t, FEObject::Node> const &nodes,
    FEObject::Bar const &bar, ebBarParameters const &ebParam)
    -> EulerBernoulliBar {

  // Return
  auto newBar = EulerBernoulliBar{};

  // Length
  auto const &node1 = nodes.at(ele2.nodesId_.at(0));
  auto const n1xyz = Vector3d{node1.xCoord_, node1.yCoord_, node1.zCoord_};
  auto const &node2 = nodes.at(ele2.nodesId_.at(1));
  auto const n2xyz = Vector3d{node2.xCoord_, node2.yCoord_, node2.zCoord_};

  auto const lenA = (n1xyz - n2xyz).norm();

  // Evaluate Mass
  newBar.localM = ebBendingMassM(lenA, ebParam.crossA, ebParam.density);

  // Evaluate Stiffness
  newBar.localK = ebBendingStiffnessK(lenA, ebParam.youngE, ebParam.momentIz);

  newBar.dofsIdx = ebParam.dofsIdx;

  return newBar;
};

} // namespace FETheory