
## #################################################################
## Targets
## #################################################################
include_directories(
  ${PROJECT_SOURCE_DIR}/statistics
  ${PROJECT_SOURCE_DIR}/gui
  ${PROJECT_SOURCE_DIR}/gui/QtCustomPlot
  )

add_subdirectory(
  QtCustomPlot
  )

add_library(negotiation_widgets ${${PROJECT_NAME}_BUILD_TYPE}
  MainWindow.cpp
  )
target_link_libraries (negotiation_widgets
  Qt5::Widgets
  binomial
  QtCustomPlot
  )
