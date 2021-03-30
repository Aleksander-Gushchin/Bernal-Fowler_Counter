file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(${invariantlib} STATIC ${srcs} ${hdrs})