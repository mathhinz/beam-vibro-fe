# Sources and Headers
set(FEMODEL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/element.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/material.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/model.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/part.cxx"
)
set(FEMODEL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/element.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/material.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/model.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/part.hxx"
)
set(FEMODEL_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

# FE Model Library
add_library(${FEMODEL_LIB} STATIC ${FEMODEL_SOURCES} ${FEMODEL_HEADERS})
target_include_directories(${FEMODEL_LIB} PUBLIC ${FEMODEL_INCLUDES})

target_link_libraries(${FEMODEL_LIB} PUBLIC ${FEOBJECTS_LIB} ${NASTRANIO_LIB})