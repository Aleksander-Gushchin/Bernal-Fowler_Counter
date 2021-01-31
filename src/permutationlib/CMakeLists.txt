file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(${permutationlib} STATIC ${srcs} ${hdrs})