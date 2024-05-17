#include "barAssemble.hxx"

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/src/SparseCore/SparseMatrix.h>
#include <bar.hxx>
#include <barMatrices.hxx>
#include <isotropic_material.hxx>
#include <line2.hxx>
#include <model.hxx>
#include <utility>
#include <variant>

namespace FETheory {

namespace {

auto createTriplets(SMatrixXd const &matrix,
                    std::vector<uint64_t> const &gDofsIdx)
    -> std::vector<Triplet> {
  auto const nonZeros = matrix.nonZeros();
  auto triplets = std::vector<Triplet>{};
  triplets.reserve(nonZeros);

  for (auto outK = 0; outK < matrix.outerSize(); outK++) {
    for (SMatrixXd::InnerIterator innIt(matrix, outK); innIt; ++innIt) {
      auto const gRow = static_cast<int>(gDofsIdx.at(innIt.row()));
      auto const gCol = static_cast<int>(gDofsIdx.at(innIt.col()));
      triplets.emplace_back(gRow, gCol, innIt.value());
    }
  }
  return triplets;
}

} // namespace

auto getBarSubsystemKandM(FEModel::System const &system,
                          FEModel::Subsystem const &subsystem)
    -> std::pair<SMatrixXd, SMatrixXd> {

  // Number of DOFs (assuming 6 per node)
  auto const dofCount = static_cast<int>(subsystem.nodesId_.size() * 6);

  // Return Matrices
  auto Kmat = SMatrixXd(dofCount, dofCount);
  auto Mmat = SMatrixXd(dofCount, dofCount);

  // Container to store spare values
  auto ssTripletsK = std::vector<Triplet>{};
  auto ssTripletsM = std::vector<Triplet>{};

  // Shell section properties
  auto const &bar = std::get<FEObject::Bar>(subsystem.part_);
  auto const barProps = FETheory::getBarSectionParameters(system, bar);

  // Create element local matrices
  for (auto const &elePair : subsystem.elements_) {
    auto const &element = elePair.second;

    // Case Line2
    if (std::holds_alternative<FEObject::Line2>(element)) {
      // Create Element Local Matrices
      auto const &line2 = std::get<FEObject::Line2>(element);
      auto barMats = getBar3DLocalKandM(line2, system.nodes_, bar, barProps);

      // Rotate to Global Coordinates
      auto const rotatedLocalK =
          (barMats.transR.transpose() * barMats.localK * barMats.transR).eval();
      auto const rotatedLocalM =
          (barMats.transR.transpose() * barMats.localM * barMats.transR).eval();

      // Global Dofs Idx
      std::vector<uint64_t> nodesId(line2.nodesId_.begin(),
                                    line2.nodesId_.end());
      auto const gDofs = subsystem.getDofsIdx(nodesId);

      // Grab matrix values as triplets mapped to global dofs
      auto tripletsEleK = createTriplets(rotatedLocalK.sparseView(), gDofs);
      auto tripletsEleM = createTriplets(rotatedLocalM.sparseView(), gDofs);

      // Assign triplets to subsystem sparse matrix
      ssTripletsK.insert(ssTripletsK.end(), tripletsEleK.begin(),
                         tripletsEleK.end());
      ssTripletsM.insert(ssTripletsM.end(), tripletsEleM.begin(),
                         tripletsEleM.end());
    }
  }

  Kmat.setFromTriplets(ssTripletsK.begin(), ssTripletsK.end());
  Mmat.setFromTriplets(ssTripletsM.begin(), ssTripletsM.end());

  auto checkM = Matrix5454d(Mmat).eval();
  auto checkK = Matrix5454d(Kmat).eval();

  return std::make_pair(Kmat, Mmat);
};

} // namespace FETheory