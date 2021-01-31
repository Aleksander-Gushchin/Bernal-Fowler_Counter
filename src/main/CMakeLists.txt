cmake_minimum_required( VERSION 3.9 )

project(Main)

add_executable(Main main.cpp)
target_link_libraries(Main ${graphlib})