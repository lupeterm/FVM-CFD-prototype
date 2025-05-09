# Google Test
include(FetchContent)

# Fetch Google Test
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        03597a01ee50ed33e9dfd640b249b4be3799d395
)
FetchContent_MakeAvailable(googletest)

# Fetch Ginkgo
FetchContent_Declare(
  ginkgo
  GIT_REPOSITORY https://github.com/ginkgo-project/ginkgo.git
  GIT_TAG        v1.9.0
)
set(GINKGO_BUILD_MPI ON CACHE INTERNAL "Enable Ginkgo MPI support")
FetchContent_MakeAvailable(ginkgo)
