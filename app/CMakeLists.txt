add_executable(Executable main.cc)

target_link_libraries(Executable PUBLIC Crow ATM nlohmann_json)
