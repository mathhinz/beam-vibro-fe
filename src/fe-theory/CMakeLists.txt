# Sources and Headers
set(FETHEORY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/barTheory.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/barMatrices.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/barAssemble.cxx"
)
set(FETHEORY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/barTheory.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/barMatrices.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/barAssemble.hxx"
)
set(FETHEORY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

# FE Objects Library
add_library(${FETHEORY_LIB} STATIC ${FETHEORY_SOURCES} ${FETHEORY_HEADERS})
target_include_directories(${FETHEORY_LIB} PUBLIC ${FETHEORY_INCLUDES})
target_link_libraries(${FETHEORY_LIB} PUBLIC ${FEMODEL_LIB} Eigen3::Eigen Spectra::Spectra)