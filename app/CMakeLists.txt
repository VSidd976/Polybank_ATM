add_executable(Executable main.cc)

target_link_libraries(Executable PUBLIC Crow ATM nlohmann_json)

if(${ENABLE_LTO})
    target_enable_lto(Executable)
endif()
