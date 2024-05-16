include(Catch)

add_executable("UnitTestVibroFE" "test_read_cards.cxx")
target_link_libraries("UnitTestVibroFE" PUBLIC ${NASTRANIO_LIB})
target_link_libraries("UnitTestVibroFE" PRIVATE Catch2::Catch2WithMain)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "UnitTestVibroFE"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

catch_discover_tests("UnitTestVibroFE")