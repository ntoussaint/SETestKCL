set(testsrcs
  BinomialCalculatorTest.cxx
  )

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/gui
  ${PROJECT_SOURCE_DIR}/gui/QtCustomPlot
  ${PROJECT_SOURCE_DIR}/statistics
  )

create_test_sourcelist(SETestKCLTests SETestKCLTests.cxx ${testsrcs})
add_executable(SETestKCLTests ${SETestKCLTests})
target_link_libraries(SETestKCLTests 
  binomial
  )

foreach(src ${testsrcs})
  get_filename_component(name ${src} NAME_WE)
  add_test(NAME ${name} COMMAND SETestKCLTests ${name})
endforeach()
