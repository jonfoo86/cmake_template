cmake_minimum_required(VERSION 2.6)

Set(TARGET test)
project(${TARGET})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -O3 ")

link_directories(/usr/local/lib /usr/local/lib64)
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
link_libraries(-static-libstdc++ -static-libgcc)

# add dependencies
# include(CMakeLists-libconfuse.cmake)

# add output library
#add_library(${TARGET} ${SOURCES})
add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} sqlite3.a pthread dl)


