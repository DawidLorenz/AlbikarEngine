# ###########################################################
# Create Albikar Engine Tests
cmake_minimum_required(VERSION 3.20)
message("############### Create Albikar Engine Tests ################")

add_executable(AlbikarEngineTest
    main.cpp
    engine/AlbikarEngine.cpp)

target_link_libraries(AlbikarEngineTest
    PRIVATE
    gtest
    AlbikarEngine)

enable_testing()

# add_custom_command(TARGET AlbikarEngineTest POST_BUILD
# COMMENT "Run ALL TESTS"
# COMMAND "C:\\Users\\dalo\\Desktop\\GitPriv\\AlbikarEngine\\build\\AlbikarEngine\\tests\\Debug\\AlbikarEngineTest.exe")

# add_custom_command(TARGET AlbikarEngineTest POST_BUILD
# COMMAND "${CMAKE_COMMAND}" -E "$<TARGET_FILE:AlbikarEngineTest>"
# COMMENT "Copying to output directory")