cmake_minimum_required(VERSION 3.1)

# Project Setting
#============================================================================
project(OpenGL_Template)

set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/output)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(TRUE_SRCDIR ${PROJECT_SOURCE_DIR}/Source)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIBS  )

OPTION(USE_SHARED_LIB "Use Shared Lib Instade of Static Lib" ON)

#  Compile Settings
#============================================================================
include_directories(
  ${TRUE_SRCDIR}/dependence/assimp/include/
  ${TRUE_SRCDIR}/dependence/glad/include/
  ${TRUE_SRCDIR}/dependence/glfw/include/
  ${TRUE_SRCDIR}/dependence/stb/
  ${TRUE_SRCDIR}/dependence/glm/
  ${TRUE_SRCDIR}/include
  )

if(MSVC)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
else(MSVC)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} --std=c++11)
  if(NOT WIN32)
    set(LIBS ${LIBS} dl)
  endif(NOT WIN32)
endif(MSVC)


#  GLFW
#============================================================================
add_subdirectory(${TRUE_SRCDIR}/dependence/glfw)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
if(USE_SHARED_LIB)
  option(BUILD_SHARED_LIBS ON)
endif(USE_SHARED_LIB)

set(LIBS ${LIBS} glfw)

#  ASSIMP
#============================================================================
add_subdirectory(${TRUE_SRCDIR}/dependence/assimp)
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
set(LIBS ${LIBS} assimp)

#  glad
#============================================================================
if(USE_SHARED_LIB)
  add_library(GLAD_LIB SHARED ${TRUE_SRCDIR}/dependence/glad/src/glad.c)
else(USE_SHARED_LIB)
  add_library(GLAD_LIB STATIC ${TRUE_SRCDIR}/dependence/glad/src/glad.c)
endif(USE_SHARED_LIB)
set(LIBS ${LIBS} GLAD_LIB)

#  stb
#============================================================================
if(USE_SHARED_LIB)
  add_library(STB_IMAGE SHARED ${TRUE_SRCDIR}/dependence/stb/deprecated/stb_image.c)
else(USE_SHARED_LIB)
  add_library(STB_IMAGE STATIC ${TRUE_SRCDIR}/dependence/stb/deprecated/stb_image.c)
endif(USE_SHARED_LIB)
set(LIBS ${LIBS} STB_IMAGE)

#  File execute
#============================================================================

file(GLOB SOURCE_FILES ${TRUE_SRCDIR}/src/*)
file(GLOB HEADER_FILES ${TRUE_SRCDIR}/include/*)
file(GLOB SHADER_FILES ${TRUE_SRCDIR}/shader/*)
file(GLOB RESOURCE_FILES ${TRUE_SRCDIR}/resource/*)

#  Executable
#============================================================================
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

#  Copy files
#============================================================================

#    Shader
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${TRUE_SRCDIR}/shader/ ${PROJECT_BINARY_DIR}/shader/
  DEPENDS SHADER_FILES
  )

#    Resources
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${TRUE_SRCDIR}/resource/ ${PROJECT_BINARY_DIR}/resource/
  DEPENDS RESOURCE_FILES
  )

