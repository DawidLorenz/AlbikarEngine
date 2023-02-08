message("-- SetUp Vulkan CMake")

find_package(Vulkan REQUIRED)
set(ALBIKAR_VULKAN_LIBRARIES ${Vulkan_LIBRARIES} CACHE INTERNAL "")
set(ALBIKAR_VULKAN_INCLUDES ${Vulkan_INCLUDE_DIRS} CACHE INTERNAL "")

message("---- Vulkan found: " ${Vulkan_FOUND})
message("---- Vulkan Include: " ${ALBIKAR_VULKAN_LIBRARIES})
message("---- Vulkan Lib: " ${ALBIKAR_VULKAN_INCLUDES})