cmake_minimum_required(VERSION 3.10)
project(GraphAlgorithmLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
        src/Graph.cpp
        src/BruteForceAlgorithm.cpp
        src/DijkstraAlgorithm.cpp
        src/BellmanFordAlgorithm.cpp
)

add_library(GraphAlgorithmLibrary STATIC ${SOURCES})


enable_testing()

set(TEST_SOURCES
        test/test_brutforce.cpp
        test/doctest_main.cpp
        test/test_graph.cpp
        test/test_dijkstra.cpp
        test/test_bellmanford.cpp
)

# Add test executable
add_executable(GraphAlgorithmTests ${TEST_SOURCES})
target_link_libraries(GraphAlgorithmTests GraphAlgorithmLibrary)

# Add test
add_test(NAME GraphAlgorithmTests COMMAND GraphAlgorithmTests)