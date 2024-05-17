#include "beamAssemble.hxx"
#include "model.hxx"
#include <chrono>
#include <filesystem>
#include <iostream>
#include <model.hxx>
#include <read_file.hxx>
#include <string>

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

    // Shell Routine
    if (std::holds_alternative<FEObject::Bar>(subsystem.part_)) {
      auto ssKandM = FETheory::getBarSubsystemKandM(feSystem, subsystem);
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