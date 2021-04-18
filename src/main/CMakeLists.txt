cmake_minimum_required( VERSION 3.9 )

project(main)

add_executable(main main.cpp)
target_link_libraries(main ${graphlib} ${permutationlib} ${invariantlib})