cmake_minimum_required (VERSION 3.2)
project(brdf)

set(CMAKE_CXX_STANDARD 17)

set(EXT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ext")

add_executable(brdf 

  # Header files
  include/brdf/BRDFAnalytic.h
  include/brdf/BRDFBase.h
  include/brdf/BRDFImageSlice.h
  include/brdf/BRDFMeasuredAniso.h
  include/brdf/BRDFMeasuredMERL.h
  include/brdf/DGLShader.h
  include/brdf/Paths.h
  include/brdf/MainWindow.h
  
  # Source files
  src/BRDFAnalytic.cpp
  src/BRDFBase.cpp
  src/BRDFImageSlice.cpp
  src/BRDFMeasuredAniso.cpp
  src/BRDFMeasuredMERL.cpp
  src/DGLShader.cpp
  src/Paths.cpp
  src/MainWindow.cpp
  src/main.cpp
  )

include_directories(include/brdf)
  
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${EXT_DIR}/glm)
target_link_libraries(brdf glm)

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${EXT_DIR}/stb_image)
target_link_libraries(brdf stb_image)

add_subdirectory(${EXT_DIR}/glfw)
include_directories(${EXT_DIR}/glfw/include)
target_link_libraries(brdf glfw ${GLFW_LIBRARIES})

add_subdirectory(${EXT_DIR}/glad)
target_link_libraries(brdf glad)

add_subdirectory(${EXT_DIR})
include_directories(${EXT_DIR}/imgui)
include_directories(${EXT_DIR}/imgui/backends)
target_link_libraries(brdf imgui)

if(MSVC)
	set_target_properties(brdf PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()
