cmake_minimum_required(VERSION 3.8)
project(Mario)

set(SP2_PATH "../SeriousProton2" CACHE STRING "Path to SeriousProton2 sources")
get_filename_component(SP2_PATH ${SP2_PATH} ABSOLUTE)
set(CMAKE_MODULE_PATH "${SP2_PATH}/cmake" ${CMAKE_MODULE_PATH})
find_package(SeriousProton2 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
serious_proton2_executable(Mario ${SOURCES})

if(WIN32)
    install(DIRECTORY resources DESTINATION ./)
endif()
