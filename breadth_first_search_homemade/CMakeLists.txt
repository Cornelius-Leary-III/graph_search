cmake_minimum_required(VERSION 3.13)
project(breadth_first_search_homemade)

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

add_executable(test_BFS
               BreadthFirstSearchPlanner.cpp BreadthFirstSearchPlanner.h
               GraphNode.cpp GraphNode.h
               GraphEdge.cpp GraphEdge.h
               Graph.cpp Graph.h BreadthFirstSearchPlanner_test.cpp)
target_link_libraries(test_BFS gtest gtest_main)
add_test(test_breadth_first_search_class test_BFS)

add_executable(test_GraphNode GraphNode_test.cpp
               GraphNode.cpp GraphNode.h)
target_link_libraries(test_GraphNode gtest gtest_main)
add_test(test_graph_node_class test_GraphNode)

add_executable(test_GraphEdge GraphEdge_test.cpp
               GraphEdge.cpp GraphEdge.h
               GraphNode.cpp GraphNode.h)
target_link_libraries(test_GraphEdge gtest gtest_main)
add_test(test_graph_edge_class test_GraphEdge)

add_executable(test_Graph Graph_test.cpp
               Graph.cpp Graph.h
               GraphEdge.cpp GraphEdge.h
               GraphNode.cpp GraphNode.h)
target_link_libraries(test_Graph gtest gtest_main)
add_test(test_graph_class test_Graph)




