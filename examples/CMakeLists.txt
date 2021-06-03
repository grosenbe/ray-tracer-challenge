add_executable(
  ProjectileTracker
  ProjectileTracker.cpp
  )

target_include_directories(
  ProjectileTracker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(
  ProjectileTracker
  raytracerchallenge)

add_executable(
  ClockFace
  ClockFace.cpp)

target_include_directories(
  ClockFace PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(
  ClockFace
  raytracerchallenge)
