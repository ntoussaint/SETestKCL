cmake_minimum_required(VERSION 3.0)
project(SETestKCL
  VERSION 1.0.0)

## #################################################################
## CMAKE options
## #################################################################

option(BUILD_SHARED_LIBS OFF)
if (BUILD_SHARED_LIBS)
  set(${PROJECT_NAME}_BUILD_TYPE SHARED)
endif()
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
if(WIN32)
  set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin)
else()
  set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)
endif(WIN32)
if (APPLE)
  set(GUI_EXECUTABLE MACOSX_BUNDLE)
endif()

## #################################################################
## Documentation
## #################################################################

option(BUILD_DOC "Build documentation" OFF)
if (BUILD_DOC)
  find_package(Doxygen)
  if (DOXYGEN)
    configure_file (doxygen.config.in doxygen.config)
    add_custom_target(doc
      ${DOXYGEN} doxygen.config
      )
  else()
    MESSAGE(WARNING "Doxygen was not found. Documentation cannot be built")
  endif()
endif()

## #################################################################
## Targets
## #################################################################

find_package(Qt5Widgets REQUIRED)

add_subdirectory(statistics)
add_subdirectory(gui)

include_directories(
  ${PROJECT_SOURCE_DIR}/statistics
  ${PROJECT_SOURCE_DIR}/gui
  )
ADD_EXECUTABLE(negotiation ${GUI_EXECUTABLE}
  Main.cpp
)
target_link_libraries (negotiation 
  negotiation_widgets
  )

## #################################################################
## Installation
## #################################################################
install(TARGETS negotiation
  BUNDLE DESTINATION bin
  RUNTIME DESTINATION bin
  )
