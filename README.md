# vibro-fe

FE Solver for Beam (Structural Dynamics)

## Description

Current file formats supported:

* .bdf

## Getting Started

Recommended Tools:

* Git
* Conan
* CMake
* Clang
* Visual Studio Code
* Ninja

### Dependencies

* Eigen
* Catch2
* Spectra

### Installing

* git clone
* cd beam-vibro-fe
* mkdir build
* conan install . --output-folder=build --build=missing --settings=build_type=Debug
* cd build
* cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++ .. -G Ninja
* ninja

### Executing program

* Launch File: fe-solver

## Help

* No support provided
  
## Authors

Contributors names and contact info

Mathias Hinz
[mathias-hinz](https://www.linkedin.com/in/mathias-hinz/)

## Version History

* 0.0.1
  * Initial Release

## License

This project is licensed under the MIT License - see the LICENSE.md file for details

