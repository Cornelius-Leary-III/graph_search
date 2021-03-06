cmake_minimum_required(VERSION 3.13)
project(BFS)

set(CMAKE_CXX_STANDARD 14)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif ()


#add_executable(BFS
#               BFS_Planner.cpp BFS_Planner.h
#               #               AdjacencyList.cpp AdjacencyList.h
#               )

add_executable(BFSPlanner_test test_BFSPlanner.cpp
               BFS_Planner.cpp BFS_Planner.h
               #               AdjacencyList.cpp AdjacencyList.h
               )

target_link_libraries(BFSPlanner_test
                      gtest_main)

add_test(test_BFS_planner_class
         BFSPlanner_test)

#add_executable(AdjacencyList_test test_AdjacencyList.cpp
#               AdjacencyList.cpp AdjacencyList.h)
#target_link_libraries(AdjacencyList_test gtest gtest_main)
#add_test(test_adjacency_list_class AdjacencyList_test)

# copy tests/ directory to build directory for use in unit tests.
add_custom_command(
     TARGET BFSPlanner_test POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
             ${CMAKE_CURRENT_SOURCE_DIR}/tests
             ${CMAKE_CURRENT_BINARY_DIR}/tests)
