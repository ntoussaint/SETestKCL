
## #################################################################
## Targets
## #################################################################

add_library(QtCustomPlot ${${PROJECT_NAME}_BUILD_TYPE}
  qcustomplot.cpp
  )
target_link_libraries (QtCustomPlot
  Qt5::Widgets
  Qt5::PrintSupport
  )
