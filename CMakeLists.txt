cmake_minimum_required( VERSION 3.9 )

project(OrgraphCount)

set(graphlib graphlib)
set(invariantlib invariantlib)
set(permutationlib permutationlib)
set(orgtest orgtest)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/gtest")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gtest")

file(GLOB SUBLIBS "${CMAKE_CURRENT_SOURCE_DIR}/src/*lib")

include_directories(${SUBLIBS})

file(GLOB SUBDIRS "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

foreach(subdir ${SUBDIRS})
  add_subdirectory(${subdir})
endforeach()



enable_testing()