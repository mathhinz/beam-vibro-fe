#pragma once

#include <Eigen/Sparse>
#include <Eigen/src/SparseCore/SparseUtil.h>
#include <model.hxx>
#include <utility>

namespace FETheory {

using Triplet = Eigen::Triplet<double_t>;
using SMatrixXd = Eigen::SparseMatrix<double_t>;
using Matrix1212d = Eigen::Matrix<double_t, 12, 12>;
using Matrix5454d = Eigen::Matrix<double_t, 54, 54>;

auto getBarSubsystemKandM(FEModel::System const &system,
                          FEModel::Subsystem const &subsystem)
    -> std::pair<SMatrixXd, SMatrixXd>;

} // namespace FETheory
