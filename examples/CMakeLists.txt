add_executable(
  ProjectileTracker
  ProjectileTracker.cpp
  )

target_include_directories(ProjectileTracker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(ProjectileTracker
  raytracerchallenge
  )
