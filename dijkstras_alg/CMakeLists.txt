cmake_minimum_required(VERSION 3.13)
project(dijkstras_alg)

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


### Edge class - unit tests
add_executable(unit_test_Edge
               EdgeSetBuilder.h EdgeSetBuilder.cpp
               unit_test_edge_class.cpp Edge.cpp Edge.h)

target_link_libraries(unit_test_Edge
                      gtest_main)

add_test(edge_unit_tests
         unit_test_Edge)


### EdgeSetBuilder class - unit tests
add_executable(unit_test_EdgeSetBuilder
               EdgeSetBuilder.h EdgeSetBuilder.cpp
               unit_test_edge_set_builder_class.cpp Edge.cpp Edge.h)

target_link_libraries(unit_test_EdgeSetBuilder
                      gtest_main)

add_test(edge_set_builder_unit_tests
         unit_test_EdgeSetBuilder)

### EdgeImporter class - unit tests
add_executable(unit_test_EdgeImporter
               Edge.h Edge.cpp
               EdgeSetBuilder.h EdgeSetBuilder.cpp
               EdgeImporter.h EdgeImporter.cpp
               unit_test_edge_importer_class.cpp)

target_link_libraries(unit_test_EdgeImporter
                      gtest_main)

add_test(edge_importer_unit_tests
         unit_test_EdgeImporter)

### Dijkstras_Alg class - unit tests
add_executable(unit_test_Dijkstras_Alg
               Dijkstras_Alg.h Dijkstras_Alg.cpp
               Edge.h Edge.cpp
               EdgeSetBuilder.h EdgeSetBuilder.cpp
               EdgeImporter.h EdgeImporter.cpp
               unit_test_setup_methods_dijkstras_alg_class.cpp
               unit_test_compute_methods_dijkstras_alg_class.cpp)

target_link_libraries(unit_test_Dijkstras_Alg
                      gtest_main)

add_test(dijkstras_algorithm_unit_tests
         unit_test_Dijkstras_Alg)

### ShortestPath class - unit tests
add_executable(unit_test_ShortestPath
               ShortestPath.h ShortestPath.cpp
               Dijkstras_Alg.h Dijkstras_Alg.cpp
               Edge.h Edge.cpp
               EdgeSetBuilder.h EdgeSetBuilder.cpp
               EdgeImporter.h EdgeImporter.cpp
               unit_test_shortest_path_class.cpp)

target_link_libraries(unit_test_ShortestPath
                      gtest_main)

add_test(shortest_path_unit_tests
         unit_test_ShortestPath)

# copy tests/ directory to build directory for use in unit tests.
add_custom_command(
     TARGET unit_test_ShortestPath POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
             ${CMAKE_CURRENT_SOURCE_DIR}/tests
             ${CMAKE_CURRENT_BINARY_DIR}/tests)
