cmake_minimum_required(VERSION 3.10)
project(GraphAlgorithmLibrary)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files for the main library
set(SOURCES
        src/Graph.cpp
        src/DijkstraAlgorithm.cpp
)

# Add the main library
add_library(GraphAlgorithmLibrary STATIC ${SOURCES})


# Add doctest and tests
enable_testing()

# Source files for tests
set(TEST_SOURCES
        test/test_graph.cpp
        test/test_dijkstra.cpp
)

# Add test executable
add_executable(GraphAlgorithmTests ${TEST_SOURCES})
target_link_libraries(GraphAlgorithmTests GraphAlgorithmLibrary)

# Add test
add_test(NAME GraphAlgorithmTests COMMAND GraphAlgorithmTests)