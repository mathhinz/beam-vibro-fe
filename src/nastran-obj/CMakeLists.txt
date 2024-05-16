# Sources and Headers
set(NASTRANOBJ_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/cbar.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/grid.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/mat1.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/pbar.cxx"
    )
set(NASTRANOBJ_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/cbar.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/grid.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/mat1.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/pbar.hxx"
    )
set(NASTRANOBJ_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

#Nastran Input/Output Library
add_library(${NASTRANOBJ_LIB} STATIC ${NASTRANOBJ_SOURCES} ${NASTRANOBJ_HEADERS})
target_include_directories(${NASTRANOBJ_LIB} PUBLIC ${NASTRANOBJ_INCLUDES})
