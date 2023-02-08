cmake_minimum_required(VERSION 3.20)
message("#################################################################")
message("######################## PROJECT ALBIKAR ########################")
project(Albikar)
option(ALBIKAR_TEST "Build all tests" ON)
option(ALBIKAR_COVERAGE "Build code coverage tests" ON) # TODO(dlorenz) add code coverage
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_GNUtoMS ON)

# Create Thirt Parts
add_subdirectory(ThirtParts)

# Create Albikar Engine
add_subdirectory(AlbikarEngine)

# Create Albikar Game Editir
add_subdirectory(AlbikarEditor)

message("#################################################################")
message("######################## PROJECT ALBIKAR ########################")