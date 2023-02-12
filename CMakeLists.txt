cmake_minimum_required(VERSION 3.20)
message("#################################################################")
message("######################## PROJECT ALBIKAR ########################")
project(Albikar)
option(ALBIKAR_TEST "Build all tests" OFF)
option(ALBIKAR_COVERAGE "Build code coverage tests" OFF) # TODO(dlorenz) add code coverage
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_GNUtoMS ON CACHE INTERNAL "")
set(ALBIKAR_CPP_STANDARD cxx_std_20 CACHE INTERNAL "")

message("-- CPP standard: " ${ALBIKAR_CPP_STANDARD})
message("-- Tests: " ${ALBIKAR_TEST})
message("-- Tests coverage: " ${ALBIKAR_COVERAGE})

# Create Thirt Parts
add_subdirectory(ThirtParts)

# Create Albikar Engine
add_subdirectory(AlbikarEngine)

# Create Albikar Game Editir
add_subdirectory(AlbikarEditor)

message("#################################################################")
message("######################## PROJECT ALBIKAR ########################")