# Sources and Headers
set(NASTRANIO_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/read_card.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/read_elem.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/read_file.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/read_grid.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/read_mat.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/read_part.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/read_util.cxx"
)
set(NASTRANIO_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/read_card.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/read_elem.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/read_file.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/read_grid.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/read_mat.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/read_part.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/read_util.hxx"
)
set(NASTRANIO_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

# Nastran Input/Output Library
add_library(${NASTRANIO_LIB} STATIC ${NASTRANIO_SOURCES} ${NASTRANIO_HEADERS})
target_include_directories(${NASTRANIO_LIB} PUBLIC ${NASTRANIO_INCLUDES})
target_link_libraries(${NASTRANIO_LIB} PUBLIC ${NASTRANOBJ_LIB})