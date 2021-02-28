cmake_minimum_required( VERSION 3.9 )

project(Test)

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${orgtest} ${srcs} ${hdrs})
target_link_libraries(${orgtest} ${graphlib} ${permutationlib} gtest)

