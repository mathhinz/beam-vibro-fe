#pragma once

#include <array>
#include <cstdint>
#include <element.hxx>
#include <material.hxx>
#include <node.hxx>
#include <part.hxx>
#include <read_file.hxx>
#include <unordered_map>
#include <vector>
namespace FEModel
{

struct Subsystem
{
    Part part_;
    std::unordered_map<uint64_t, Element> elements_;
    std::vector<uint64_t> nodesId_;
    std::unordered_map<uint64_t, std::array<uint64_t, 6>> dofsIdxPerNodeId_;

    auto getDofsIdx(std::vector<uint64_t> const &nodesId) const
        -> std::vector<uint64_t>;
};

struct System
{
    std::unordered_map<uint64_t, Subsystem> subsystems_;
    std::unordered_map<uint64_t, FEObject::Node> nodes_;
    std::unordered_map<uint64_t, Material> materials_;
};

auto loadSystem(NastranIO::NastranObjects const &nasInputs) -> System;

} // namespace FEModel