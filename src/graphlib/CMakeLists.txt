file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(${graphlib} STATIC ${srcs} ${hdrs})