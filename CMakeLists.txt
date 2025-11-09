cmake_minimum_required(VERSION 3.22)

project("Polybank_ATM" VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

option(ENABLE_TESTING "Enable a Unit tests build" ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(CPM)

cpmaddpackage("gh:CrowCpp/Crow#v1.3.0")
cpmaddpackage("gh:nlohmann/json#v3.12.0")
# cpmaddpackage("gh:libcpr/cpr#1.12.0")

add_subdirectory(src)
add_subdirectory(inc)

if(${ENABLE_TESTING})
    cpmaddpackage("gh:catchorg/Catch2#v3.11.0")
    list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(app)
