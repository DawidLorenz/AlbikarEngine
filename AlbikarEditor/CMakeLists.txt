# ###########################################################
# Create Albikar Game Editor
cmake_minimum_required(VERSION 3.20)
message("################### Create Albikar Game Editor ##################")

# ###########################################################
# ###########################################################
# Project properties
project(AlbikarEditor
    VERSION 0.1.0
    DESCRIPTION "Albikar Editor"
    LANGUAGES CXX)

# ###########################################################
include(cmake/imgui.cmake) # ImGui Package

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# #############################################

# Add all cpp files
file(GLOB AlbikarGameEditor_SRC
    src/*.cpp
    src/*.hpp
    src/core/*.cpp
    src/core/*.hpp
    src/gui/*.cpp
    src/gui/*.hpp
    src/gui/guiRenderEngine/*.cpp
    src/gui/guiRenderEngine/*.hpp
    src/platform/*.cpp
    src/platform/*.hpp
    src/utils/*.cpp
    src/utils/*.hpp)

# Add include path
set(AlbikarDirectory
    src/core/
    src/gui/
    src/gui/guiRenderEngine/
    src/platform/
    src/utils/
    src/
    thirtParts/glfw/include/
    thirtParts/imgui/
    thirtParts/imgui/backends/
    thirtParts/AlbikarEngine/include/) # AlbikarEngine

add_executable(AlbikarEditor ${AlbikarGameEditor_SRC})
target_compile_features(AlbikarEditor PRIVATE cxx_std_20)

# ###########################################################
# ###################  FINAL SETUP  #########################
# ###########################################################
# Include Directory
target_compile_definitions(AlbikarEditor PUBLIC ${ALBIKAR_IMGUI_DEFINES})
target_include_directories(AlbikarEditor
    PRIVATE
    ${AlbikarDirectory}
    ${ALBIKAR_VULKAN_INCLUDES}
    ${ALBIKAR_GLFW_INCLUDES}
    ${ALBIKAR_IMGUI_INCLUDES}
    ${ALBIKAR_ENGINE_INCLUDE_DIR})

# Link library
target_link_libraries(AlbikarEditor
    ${ALBIKAR_VULKAN_LIBRARIES}
    ${ALBIKAR_GLFW_LIBRARIES}
    ${ALBIKAR_IMGUI_LIBRARIES}
    ${ALBIKAR_LIBRARIES}
    AlbikarEngine)

set_target_properties(AlbikarEditor PROPERTIES OUTPUT_NAME "AlbikarEditor")

add_custom_command(TARGET AlbikarEditor POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy
    "$<TARGET_FILE:AlbikarEngine>"
    "$<CONFIGURATION>/$<TARGET_FILE_NAME:AlbikarEngine>"
    COMMENT "Copying to output directory")

add_custom_command(TARGET AlbikarEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/imgui.ini "$<CONFIGURATION>/imgui.ini")