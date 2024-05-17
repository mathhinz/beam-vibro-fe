#pragma once

#include <Eigen/Sparse>
#include <Eigen/src/SparseCore/SparseUtil.h>
#include <model.hxx>
#include <utility>

namespace FETheory {

using Triplet = Eigen::Triplet<double_t>;
using SMatrixXd = Eigen::SparseMatrix<double_t>;
using Matrix88d = Eigen::Matrix<double_t, 8, 8>;

auto getBarSubsystemKandM(FEModel::System const &system,
                          FEModel::Subsystem const &subsystem)
    -> std::pair<SMatrixXd, SMatrixXd>;

} // namespace FETheory
