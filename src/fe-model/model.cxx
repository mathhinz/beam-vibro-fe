#include "model.hxx"

#include <algorithm>
#include <array>
#include <bar.hxx>
#include <cbar.hxx>
#include <isotropic_material.hxx>
#include <line2.hxx>
#include <node.hxx>
#include <numeric>
#include <read_file.hxx>

namespace FEModel {

namespace {
auto generateSubsystemDOFs(Subsystem &subs, uint64_t nodeId) -> void {
  auto const iter =
      std::find(subs.nodesId_.begin(), subs.nodesId_.end(), nodeId);
  if (iter != subs.nodesId_.end()) {
    auto const nodeIdx = std::distance(subs.nodesId_.begin(), iter);
    std::array<uint64_t, 6> dofsIdx = {0, 0, 0, 0, 0, 0};
    std::iota(dofsIdx.begin(), dofsIdx.end(), nodeIdx * 6);
    subs.dofsIdxPerNodeId_[nodeId] = dofsIdx;
  }
}

} // namespace

auto Subsystem::getDofsIdx(std::vector<uint64_t> const &nodesId) const
    -> std::vector<uint64_t> {
  auto dofsIdx = std::vector<uint64_t>{};
  for (auto const &nodeId : nodesId) {
    auto iter = this->dofsIdxPerNodeId_.find(nodeId);
    if (iter != this->dofsIdxPerNodeId_.end()) {
      dofsIdx.insert(dofsIdx.end(), iter->second.begin(), iter->second.end());
    }
  }
  return dofsIdx;
};

auto loadSystem(NastranIO::NastranObjects const &nasInputs) -> System {
  auto system = System{};

  // Add node to the System
  for (auto const &grid : nasInputs.gridMap) {
    system.nodes_[grid.first] =
        FEObject::Node{grid.second.getID(), grid.second.getX1(),
                       grid.second.getX2(), grid.second.getX3()};
  }

  // Add materials to the System
  for (auto const &mat1 : nasInputs.mat1Map) {
    system.materials_[mat1.first] = FEObject::IsotropicMaterial{
        mat1.second.getMID(), mat1.second.getRHO(), mat1.second.getE(),
        mat1.second.getG(), mat1.second.getNU()};
  }

  // Add Subsystems to the System
  for (auto const &[pbarId, pbar] : nasInputs.pbarMap) {
    auto subsystem = Subsystem{};
    subsystem.part_ = FEObject::Bar{pbar.getPID(), pbar.getMID(), pbar.getA(),
                                    pbar.getI1(),  pbar.getI2(),  pbar.getJ()};
    system.subsystems_[pbarId] = subsystem;
  }

  // Add elements (and respective nodes) to their respective Subsystem
  for (auto const &[cbarId, cbar] : nasInputs.cbarMap) {
    auto &subsys = system.subsystems_.at(cbar.getPID());
    subsys.elements_[cbarId] = FEObject::Line2{cbar.getEID(),
                                               cbar.getPID(),
                                               {cbar.getGA(), cbar.getGB()},
                                               cbar.getX()};
    subsys.nodesId_.emplace_back(cbar.getGA());
    subsys.nodesId_.emplace_back(cbar.getGB());
  }

  // Make nodes unique in Subsystem and generate DOFs per Node
  for (auto &[ssId, subsys] : system.subsystems_) {
    auto &ids = subsys.nodesId_;
    std::sort(ids.begin(), ids.end());
    ids.erase(unique(ids.begin(), ids.end()), ids.end());
    for (auto const &nodeId : ids) {
      generateSubsystemDOFs(subsys, nodeId);
    }
  }

  return system;
};

} // namespace FEModel
