CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(OpenGL_Template)

SET(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/output)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Libraries
######################################################

###########################
#           GLFW          #
###########################
OPTION(GLFW_BUILD_EXAMPLES OFF)
OPTION(GLFW_BUILD_TESTS OFF)
OPTION(GLFW_BUILD_DOCS OFF)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/dependence/glfw)

###########################
#         ASSIMP          #
###########################
OPTION(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
OPTION(ASSIMP_BUILD_SAMPLES OFF)
OPTION(ASSIMP_BUILD_TESTS OFF)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/dependence/assimp)

###########################
#         ASSIMP          #
###########################
ADD_LIBRARY(STB_IMAGE STATIC ${PROJECT_SOURCE_DIR}/dependence/stb/deprecated/stb_image.c)

#         COMPILE         
######################################################
IF(MSVC)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
ELSE()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
  IF(NOT WIN32)
    SET(GLAD_LIBRARIES dl)
  ENDIF()
ENDIF()

INCLUDE_DIRECTORIES(

  ${PROJECT_SOURCE_DIR}/dependence/assimp/include/
  ${PROJECT_SOURCE_DIR}/dependence/glfw/include/
  ${PROJECT_SOURCE_DIR}/dependence/glad/include/
  ${PROJECT_SOURCE_DIR}/dependence/glm/
  ${PROJECT_SOURCE_DIR}/dependence/stb/
  ${PROJECT_SOURCE_DIR}/include/
  )

FILE(GLOB DEPENDENCE_SOURCE ${PROJECT_SOURCE_DIR}/dependence/glad/src/glad.c)
FILE(GLOB HEADERS_SOURCE ${PROJECT_SOURCE_DIR}/include/*.hpp)
FILE(GLOB SHADER_SOURCE ${PROJECT_SOURCE_DIR}/shader/*)
FILE(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB RESOURCES_FILES ${PROJECT_SOURCE_DIR}/resources/*)

SOURCE_GROUP("DEPENDENCE" FILES ${DEPENDENCE_SOURCE})
SOURCE_GROUP("Headers" FILES ${PROJECT_HEADERS})
SOURCE_GROUP("Shaders" FILES ${SHADER_SOURCE})
SOURCE_GROUP("Sources" FILES ${SOURCE_FILES})


add_executable(
  ${PROJECT_NAME}
  
  ${SOURCE_FILES}
  ${DEPENDENCE_SOURCE}
  ${HEADERS_SOURCE}
  ${SHADER_SOURCE}
  )

target_link_libraries(${PROJECT_NAME} assimp glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} STB_IMAGE)

# Copy Files
######################################################
FOREACH(SHADERS ${SHADER_SOURCE})
  FILE(COPY ${SHADERS} DESTINATION ${PROJECT_BINARY_DIR}/shader)
ENDFOREACH()


FOREACH(RESOURCES ${RESOURCES_FILES})
  FILE(COPY ${RESOURCES} DESTINATION ${PROJECT_BINARY_DIR}/resources)
ENDFOREACH()


