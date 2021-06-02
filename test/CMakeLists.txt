add_executable(raytracerchallenge-test
  Ch1-test.cpp
  Ch2-test.cpp
  Ch3-test.cpp
  Ch4-test.cpp)

target_include_directories(raytracerchallenge-test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(raytracerchallenge-test
  raytracerchallenge
  gtest
  gtest_main
  pthread)
