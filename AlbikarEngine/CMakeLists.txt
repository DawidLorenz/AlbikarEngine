# ###########################################################
# Create Albikar Engine
cmake_minimum_required(VERSION 3.20)
message("##################### Create Albikar Engine #####################")

# ###########################################################
# ###########################################################
# Project properties
project(AlbikarEngine
    VERSION 0.1.0
    DESCRIPTION "Albikar Game Engine"
    LANGUAGES CXX)

# ###########################################################
include(cmake/shader.cmake) # Shader compile
include(cmake/glm.cmake) # GLM Package

# if(MSVC)
# add_compile_options(/W4 /WX)
# else()
# add_compile_options(-Wall -Wextra -pedantic -Werror)
# endif()
file(GLOB MODULE_FILES
    include/*.hpp
    src/utils/*.cpp
    src/utils/*.hpp
    src/ai/*.cpp
    src/ai/*.hpp
    src/audio/*.cpp
    src/audio/*.hpp
    src/core/*.cpp
    src/core/*.hpp
    src/debug/*.cpp
    src/debug/*.hpp
    src/engine/*.cpp
    src/engine/*.hpp
    src/global/*.cpp
    src/global/*.hpp
    src/graphics/*.cpp
    src/graphics/*.hpp
    src/input/*.cpp
    src/input/*.hpp
    src/physics/*.cpp
    src/physics/*.hpp
    src/platform/*.cpp
    src/platform/*.hpp
    src/render/*.cpp
    src/render/*.hpp
    src/render/vulkan/*.cpp
    src/render/vulkan/*.hpp
    src/screen/*.cpp
    src/screen/*.hpp
    src/scripting/*.cpp
    src/scripting/*.hpp
    src/window/*.cpp
    src/window/*.hpp
    src/*.cpp
    src/*.hpp)

set(AlbikarEngineDirectory
    include/
    src/
    src/utils/
    src/ai/
    src/audio/
    src/core/
    src/debug/
    src/engine/
    src/global/
    src/graphics/
    src/inpput/
    src/physics/
    src/platform/
    src/render/
    src/screen/
    src/scripting/
    src/window/)

# TODO(dlorenz) make in SHARED AND STATIC
add_library(AlbikarEngine SHARED ${MODULE_FILES})

target_compile_features(AlbikarEngine PRIVATE ${ALBIKAR_CPP_STANDARD})

# TODO(dlorenz) remove for STATIC Lib
target_compile_definitions(AlbikarEngine PRIVATE DLIB_EXPORTS=1)

# Include Directory
target_include_directories(AlbikarEngine
    PRIVATE
    ${ALBIKAR_PUGIXML_INCLUDES}
    ${AlbikarEngineDirectory}
    ${ALBIKAR_VULKAN_INCLUDES}
    ${ALBIKAR_GLFW_INCLUDES})

target_link_libraries(AlbikarEngine
    glm
    ${ALBIKAR_PUGIXML_LIBRARIES}
    ${ALBIKAR_VULKAN_LIBRARIES}
    ${ALBIKAR_GLFW_LIBRARIES})

install(TARGETS AlbikarEngine DESTINATION AlbikarEngine-bin)
install(FILES
    include/AlbikarDefines.hpp
    include/IAlbikarEngine.hpp
    include/IAlbikarDebug.hpp
    include/IAlbikarWindow.hpp
    DESTINATION AlbikarEngine-include)

add_custom_command(TARGET AlbikarEngine PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/AlbikarEngine/include ${CMAKE_SOURCE_DIR}/AlbikarEditor/thirtParts/AlbikarEngine/include)

add_subdirectory(tests)
