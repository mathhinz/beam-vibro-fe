#include "barMatrices.hxx"

#include <Eigen/Dense>
#include <bar.hxx>
#include <barTheory.hxx>
#include <isotropic_material.hxx>
#include <line2.hxx>
#include <model.hxx>
#include <node.hxx>
#include <unordered_map>
#include <variant>

namespace FETheory {

namespace {
auto cosineSimilarity(Vector3d const &vec1, Vector3d const &vec2) -> double_t {
  return vec1.dot(vec2) / (vec1.norm() * vec2.norm());
}

auto elementRotation(Vector3d const &n1xyz, Vector3d const &n2xyz,
                     Vector3d const &orientation) -> Matrix33d {
  auto xDir = (n2xyz - n1xyz).eval();
  xDir /= xDir.norm();
  auto zDir = orientation.cross(xDir).eval();
  zDir /= zDir.norm();
  auto yDir = xDir.cross(zDir).eval();
  yDir /= yDir.norm();

  auto lDir = Matrix33d::Zero().eval();
  lDir.row(0) = xDir;
  lDir.row(1) = yDir;
  lDir.row(2) = zDir;

  auto gDir = Matrix33d::Identity().eval();

  auto rotT = Matrix33d::Zero().eval();
  for (auto iLoc = 0; iLoc < 3; iLoc++) {
    for (auto iGlo = 0; iGlo < 3; iGlo++) {
      rotT(iLoc, iGlo) = cosineSimilarity(lDir.row(iLoc), gDir.row(iGlo));
    }
  }

  return rotT;
};

} // namespace

auto getBarSectionParameters(FEModel::System const &system,
                             FEObject::Bar const &bar) -> BarSectionParameters {

  // Result
  auto properties = BarSectionParameters{};

  // Material
  auto const &mat = system.materials_.at(bar.matId_);
  if (std::holds_alternative<FEObject::IsotropicMaterial>(mat)) {
    auto const &isoMat = std::get<FEObject::IsotropicMaterial>(mat);
    properties.density = isoMat.rho_;
    properties.youngE = isoMat.E1_;
    properties.shearG = isoMat.G12_;
  }

  // Geometry
  // Petyt Convention:
  // X - along length
  // Y and Z - cross-section
  properties.sectionA = bar.crossArea_;
  properties.momentI1 = bar.momentInertia1;
  properties.momentI2 = bar.momentInertia2;
  properties.momentJ = bar.torsionalConst;
  properties.torsionK = bar.polarInertia;

  return properties;
}

auto getBar3DLocalKandM(
    FEObject::Line2 const &ele2,
    std::unordered_map<uint64_t, FEObject::Node> const &nodes,
    FEObject::Bar const &bar, BarSectionParameters const &barSec) -> Bar3D {

  // Return
  auto newBar = Bar3D{};

  // Nodes coordinates
  auto const &node1 = nodes.at(ele2.nodesId_.at(0));
  auto const n1xyz = Vector3d{node1.xCoord_, node1.yCoord_, node1.zCoord_};
  auto const &node2 = nodes.at(ele2.nodesId_.at(1));
  auto const n2xyz = Vector3d{node2.xCoord_, node2.yCoord_, node2.zCoord_};

  //

  // Rotation Matrix to Global Coordinates
  auto const orientation =
      Vector3d{ele2.direction_[0], ele2.direction_[1], ele2.direction_[2]};
  auto rotT33 = elementRotation(n1xyz, n2xyz, orientation);
  auto rot33 = Matrix33d::Identity().eval();
  auto rotT66 = Matrix66d::Zero().eval();
  rotT66.topLeftCorner(3, 3) = rotT33;
  rotT66.bottomRightCorner(3, 3) = rotT33;
  for (auto iNode = 0; iNode < 2; iNode++) {
    newBar.transR.block(iNode * 6, iNode * 6, 6, 6) = rotT66;
  }

  // Element size
  auto const lenA = (n1xyz - n2xyz).norm() / 2.0;

  // Evaluate In-Plane Mass
  newBar.localM =
      barTimoshenkoMassM(lenA, barSec.density, barSec.sectionA, barSec.momentI1,
                         barSec.momentI2, barSec.momentJ);

  // Evaluate In-Plane Stiffness
  newBar.localK = barTimoshenkoStiffnessK(lenA, barSec.youngE, barSec.shearG,
                                          barSec.sectionA, barSec.momentI1,
                                          barSec.momentI2, barSec.torsionK);

  return newBar;
};

} // namespace FETheory