#include "beamAssemble.hxx"

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/src/SparseCore/SparseMatrix.h>
#include <bar.hxx>
#include <beamFlex.hxx>
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

  // Number of DOFs (assuming 2 per node)
  auto const dofCount = static_cast<int>(subsystem.nodesId_.size() * 2);

  // Return Matrices
  auto Kmat = SMatrixXd(dofCount, dofCount);
  auto Mmat = SMatrixXd(dofCount, dofCount);

  // Container to store spare values
  auto ssTripletsK = std::vector<Triplet>{};
  auto ssTripletsM = std::vector<Triplet>{};

  // Bar section properties
  auto const &bar = std::get<FEObject::Bar>(subsystem.part_);
  auto const barParams = FETheory::getEuBeBarParameters(system, bar);

  // Create element local matrices
  for (auto const &elePair : subsystem.elements_) {
    auto const &element = elePair.second;

    // Case Line2
    if (std::holds_alternative<FEObject::Line2>(element)) {
      // Create Element Local Matrices
      auto const &line2 = std::get<FEObject::Line2>(element);
      auto ebBar =
          getBendingBeamLocalKandM(line2, system.nodes_, bar, barParams);

      // Rotate to Global Coordinates
      // not necessary for eb beam example
      auto const &rotatedLocalK = ebBar.localK;
      auto const &rotatedLocalM = ebBar.localM;

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

  return std::make_pair(Kmat, Mmat);
};

} // namespace FETheory