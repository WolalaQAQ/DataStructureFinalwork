cmake_minimum_required(VERSION 3.20)
project(DataStructureFinalWork)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

aux_source_directory(src DIR_SRCS)

add_executable(problem_a
        problem_a.cpp
        src/graph.cpp
        src/disjoint_sets.cpp
        src/mst.cpp
)

set_target_properties(problem_a PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/problem_a
        )

add_executable(problem_b
        problem_b.cpp
        src/graph.cpp
        src/grid_search.cpp)

set_target_properties(problem_b PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/problem_b
        )

add_custom_target(
        BUILD_ALL
        DEPENDS problem_a problem_b
)
