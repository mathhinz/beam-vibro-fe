########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(spectra_FIND_QUIETLY)
    set(spectra_MESSAGE_MODE VERBOSE)
else()
    set(spectra_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/spectraTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${spectra_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(spectra_VERSION_STRING "1.0.1")
set(spectra_INCLUDE_DIRS ${spectra_INCLUDE_DIRS_DEBUG} )
set(spectra_INCLUDE_DIR ${spectra_INCLUDE_DIRS_DEBUG} )
set(spectra_LIBRARIES ${spectra_LIBRARIES_DEBUG} )
set(spectra_DEFINITIONS ${spectra_DEFINITIONS_DEBUG} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${spectra_BUILD_MODULES_PATHS_DEBUG} )
    message(${spectra_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


