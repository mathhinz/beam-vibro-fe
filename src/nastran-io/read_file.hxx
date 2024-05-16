#pragma once

#include <cbar.hxx>
#include <cstdint>
#include <filesystem>
#include <grid.hxx>
#include <mat1.hxx>
#include <pbar.hxx>
#include <unordered_map>

using CBAR = NastranObject::CBAR;
using GRID = NastranObject::GRID;
using MAT1 = NastranObject::MAT1;
using PBAR = NastranObject::PBAR;

namespace NastranIO {

struct NastranObjects {
  std::unordered_map<uint64_t, CBAR> cbarMap;
  std::unordered_map<uint64_t, GRID> gridMap;
  std::unordered_map<uint64_t, MAT1> mat1Map;
  std::unordered_map<uint64_t, PBAR> pbarMap;
};

auto readNastranFile(const std::filesystem::path &filePath) -> NastranObjects;

} // namespace NastranIO