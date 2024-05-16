#include "read_file.hxx"

#include <fstream>
#include <iostream>
#include <read_card.hxx>
#include <read_elem.hxx>
#include <read_grid.hxx>
#include <read_mat.hxx>
#include <read_part.hxx>
#include <string>
#include <vector>

namespace NastranIO {

namespace {

auto createObjects(std::vector<Card> &cards) -> NastranObjects {
  auto objs = NastranObjects{};
  for (auto &card : cards) {
    if (card.key == "CBAR") {
      auto const newBar = readCBAR(card.lines);
      objs.cbarMap[newBar.getEID()] = newBar;
    }
    if (card.key == "GRID") {
      auto const newGrid = readGRID(card.lines);
      objs.gridMap[newGrid.getID()] = newGrid;
    }
    if (card.key == "MAT1") {
      auto const newMat1 = readMAT1(card.lines);
      objs.mat1Map[newMat1.getMID()] = newMat1;
    }
    if (card.key == "PBAR") {
      auto const newPBar = readPBAR(card.lines);
      objs.pbarMap[newPBar.getPID()] = newPBar;
    }
  }
  return objs;
};

} // namespace

auto readNastranFile(const std::filesystem::path &filePath) -> NastranObjects {

  // Output
  auto nastranObjs = NastranObjects{};

  // Open File
  auto file = std::ifstream{};
  file.open(filePath.string(), std::ifstream::in);

  // Proceed if is NASTRAN format
  auto extension = filePath.extension().string();
  if (extension == ".bdf") {
    // Retrieve supported cards info
    auto cards = parseCards(file);

    // Create objects from retrieved cards
    nastranObjs = createObjects(cards);
  } else {
    // Skip reading
    std::cout << "File format .bdf not recognized" << std::endl;
  }
  return nastranObjs;
};

}; // namespace NastranIO
