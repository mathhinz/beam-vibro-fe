set(SOLVER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cxx")

add_executable(${SOLVER_EXE} ${SOLVER_SOURCES})

target_link_libraries(${SOLVER_EXE} PUBLIC ${FEMODEL_LIB})
