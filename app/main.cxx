#include <Eigen/Sparse>
#include <barAssemble.hxx>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <model.hxx>
#include <read_file.hxx>
#include <string>
#include <Eigen/Eigenvalues>
namespace {
auto writeToFile(std::string const &path, std::string const &name,
                 FETheory::SMatrixXd const &mat) -> void {

  std::ofstream file(path + "/" + name + ".txt");
  if (file.is_open()) {
    for (int k = 0; k < mat.outerSize(); ++k)
      for (Eigen::SparseMatrix<double_t>::InnerIterator it(mat, k); it; ++it) {
        file << it.row() << " " << it.col() << " " << it.value() << " " << '\n';
      }
  }
  file.close();
}
} // namespace

int main() {

  // Start the timer
  auto start = std::chrono::high_resolution_clock::now();

  // File Path (to be replaced by main arguments)
  auto const filePath = std::string{"/Users/mathiashinz/Downloads/beam.bdf"};

  // Read model from .bdf info
  auto const path = std::filesystem::path{filePath};
  auto const nasObjs = NastranIO::readNastranFile(path);

  // Load model content
  auto const feSystem = FEModel::loadSystem(nasObjs);

  // Create FE Matrices for Subsystems
  for (auto const &ssPair : feSystem.subsystems_) {
    auto const &subsystem = ssPair.second;

    // Bar Routine
    if (std::holds_alternative<FEObject::Bar>(subsystem.part_)) {
      auto ssKandM = FETheory::getBarSubsystemKandM(feSystem, subsystem);
  
      writeToFile(path.parent_path().string(), "stifMatrix", ssKandM.first);
      writeToFile(path.parent_path().string(), "massMatrix", ssKandM.second);
    }
  }

  // End the timer
  auto end = std::chrono::high_resolution_clock::now();

  // Calculate the duration
  std::chrono::duration<double> duration = end - start;
  std::cout << "Execution time: " << duration.count() << " seconds."
            << std::endl;

  system("pause");
  return 0;
}