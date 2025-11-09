if (${ENABLE_TESTING})
    include(Catch)
    add_executable(unit_tests main.cc)
    target_include_directories(unit_tests PUBLIC ./)
    target_link_libraries(unit_tests PUBLIC ATM Catch2::Catch2WithMain)

    catch_discover_tests(unit_tests)
endif()
