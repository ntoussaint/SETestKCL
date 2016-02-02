## #################################################################
## Targets
## #################################################################

find_package(Boost REQUIRED)

include_directories(
  ${Boost_INCLUDE_DIRS}
  )
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)

add_library(binomial ${${PROJECT_NAME}_BUILD_TYPE}
  BinomialCalculator.cpp
  )
target_link_libraries (binomial
  )
