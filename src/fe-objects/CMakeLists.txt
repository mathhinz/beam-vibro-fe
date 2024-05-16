# Sources and Headers
set(FEOBJECTS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/isotropic_material.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/node.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/bar.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/line2.cxx"
)
set(FEOBJECTS_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/isotropic_material.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/node.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/bar.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/line2.hxx"
)
set(FEOBJECTS_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

# FE Objects Library
add_library(${FEOBJECTS_LIB} STATIC ${FEOBJECTS_SOURCES} ${FEOBJECTS_HEADERS})
target_include_directories(${FEOBJECTS_LIB} PUBLIC ${FEOBJECTS_INCLUDES})