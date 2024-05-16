########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(spectra_COMPONENT_NAMES "")
list(APPEND spectra_FIND_DEPENDENCY_NAMES Eigen3)
list(REMOVE_DUPLICATES spectra_FIND_DEPENDENCY_NAMES)
set(Eigen3_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(spectra_PACKAGE_FOLDER_DEBUG "/Users/mathiashinz/.conan2/p/spect220d06ce9e4fa/p")
set(spectra_BUILD_MODULES_PATHS_DEBUG )


set(spectra_INCLUDE_DIRS_DEBUG "${spectra_PACKAGE_FOLDER_DEBUG}/include")
set(spectra_RES_DIRS_DEBUG )
set(spectra_DEFINITIONS_DEBUG )
set(spectra_SHARED_LINK_FLAGS_DEBUG )
set(spectra_EXE_LINK_FLAGS_DEBUG )
set(spectra_OBJECTS_DEBUG )
set(spectra_COMPILE_DEFINITIONS_DEBUG )
set(spectra_COMPILE_OPTIONS_C_DEBUG )
set(spectra_COMPILE_OPTIONS_CXX_DEBUG )
set(spectra_LIB_DIRS_DEBUG )
set(spectra_BIN_DIRS_DEBUG )
set(spectra_LIBRARY_TYPE_DEBUG UNKNOWN)
set(spectra_IS_HOST_WINDOWS_DEBUG 0)
set(spectra_LIBS_DEBUG )
set(spectra_SYSTEM_LIBS_DEBUG )
set(spectra_FRAMEWORK_DIRS_DEBUG )
set(spectra_FRAMEWORKS_DEBUG )
set(spectra_BUILD_DIRS_DEBUG )
set(spectra_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(spectra_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${spectra_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${spectra_COMPILE_OPTIONS_C_DEBUG}>")
set(spectra_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${spectra_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${spectra_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${spectra_EXE_LINK_FLAGS_DEBUG}>")


set(spectra_COMPONENTS_DEBUG )