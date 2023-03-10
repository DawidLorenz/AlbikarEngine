message("-- SetUp PugiXML CMake")
add_subdirectory(${CMAKE_SOURCE_DIR}/ThirtParts/pugixml)

set(PUGIXML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/ThirtParts/pugixml/src)
set(PUGIXML_DEFINITIONS)
set(PUGIXML_LIBRARIES pugixml-static)

set(ALBIKAR_PUGIXML_LIBRARIES ${PUGIXML_LIBRARIES} CACHE INTERNAL "")
set(ALBIKAR_PUGIXML_INCLUDES ${PUGIXML_INCLUDE_DIR} CACHE INTERNAL "")
set(ALBIKAR_PUGIXML_DEFINES ${PUGIXML_DEFINITIONS} CACHE INTERNAL "")

message("---- PUGIXML Include: " ${ALBIKAR_PUGIXML_INCLUDES})
message("---- PUGIXML Lib: " ${ALBIKAR_PUGIXML_LIBRARIES})
message("---- PUGIXML Defines: " ${ALBIKAR_PUGIXML_DEFINES})