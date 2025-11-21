include(Catch)
add_executable(unit_tests main.cc)
target_link_libraries(unit_tests PUBLIC TestBank Catch2::Catch2WithMain)

catch_discover_tests(unit_tests)
