cmake_minimum_required(VERSION 3.0)

project(SETestKCL
  VERSION 1.0.0)

set(${PROJECT_NAME}_BUILD_TYPE STATIC)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

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

find_package(Qt5Widgets REQUIRED)

add_subdirectory(gui)
add_subdirectory(statistics)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/gui
  ${PROJECT_SOURCE_DIR}/statistics
  )

ADD_EXECUTABLE(negotiation
  Main.cpp
)
target_link_libraries (negotiation 
  negotiation_widgets
  )
