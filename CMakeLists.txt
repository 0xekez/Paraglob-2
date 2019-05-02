cmake_minimum_required (VERSION 3.14)

project(paraglob)

set(CMAKE_CXX_FLAGS "-Wall -O2")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(ahocorasick)

set(SOURCES src/paraglob.cpp ahocorasick/AhoCorasickPlus.cpp )

add_library(paraglob STATIC ${SOURCES})

target_link_libraries(paraglob ahocorasick)

install(TARGETS paraglob DESTINATION lib)
install(FILES ahocorasick.h DESTINATION include)
