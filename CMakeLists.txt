cmake_minimum_required(VERSION 3.24)

project(nastran-io VERSION 0.0.1 LANGUAGES CXX)

# Global CMake Variables
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Warning Options
option(ENABLE_WARNING "Enable Target Warnings." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable Warnings as Errors." ON)

# Linter Options
option(ENABLE_CLANG_TIDY "Enable Clang-Tidy." ON)
option(ENABLE_CPPCHECK "Enable CppCheck." OFF)

# Format Options
option(ENABLE_CLANG_FORMAT "Enable Clang-Format." ON)
option(ENABLE_CMAKE_FORMAT "Enable CMake-Format." ON)

# Test Options
option(ENABLE_TESTING "Enable a Unit Testing build." ON)

# Project/Library Names
set(NASTRANOBJ_LIB "nastran-obj")
set(NASTRANIO_LIB "nastran-io")
set(FEOBJECTS_LIB "fe-objects")
set(FEMODEL_LIB "fe-model")
set(SOLVER_EXE "fe-solver")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(Warnings)
include(Tools)

add_cmake_format_target()
add_clang_format_target()

# External Libraries
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

find_package(Eigen3 REQUIRED)
find_package(spectra REQUIRED)

if(ENABLE_TESTING)
    find_package(Catch2 REQUIRED)
    list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
endif()

# Sub Directories
add_subdirectory(src)
add_subdirectory(app)

# Test Directory
if(ENABLE_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

# Install Targets
install(
    TARGETS ${SOLVER_EXE}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(
    TARGETS ${FEMODEL_LIB}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)

install(
    TARGETS ${FEOBJECTS_LIB}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)

install(
    TARGETS ${NASTRANIO_LIB}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)

install(
    TARGETS ${NASTRANOBJ_LIB}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)