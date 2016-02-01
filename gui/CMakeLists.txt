
## #################################################################
## Targets
## #################################################################

add_library(negotiation_widgets ${${PROJECT_NAME}_BUILD_TYPE}
  MainWindow.cpp
  )
target_link_libraries (negotiation_widgets
  Qt5::Widgets
  binomial
  )
