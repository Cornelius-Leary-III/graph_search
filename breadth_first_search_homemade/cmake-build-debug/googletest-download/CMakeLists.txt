cmake_minimum_required(VERSION 2.8.2)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        "/home/carpenter/software/cpp/graphs/search/breadth_first_search_homemade/cmake-build-debug/googletest-src"
  BINARY_DIR        "/home/carpenter/software/cpp/graphs/search/breadth_first_search_homemade/cmake-build-debug/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
