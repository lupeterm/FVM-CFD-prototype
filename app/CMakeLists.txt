add_executable(
  heatConduction
  heatConduction.cpp
)

target_link_libraries(
  heatConduction
  MyLibrary
  ginkgo
)
# target_include_directories(
#   heatConduction
#   PRIVATE
#   ${CMAKE_CURRENT_SOURCE_DIR}/include
# )