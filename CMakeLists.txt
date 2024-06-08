cmake_minimum_required(VERSION 3.27)
project(build-ship-dbg-wasm)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

add_subdirectory(src)
