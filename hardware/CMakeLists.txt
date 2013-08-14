cmake_minimum_required(VERSION 2.7)
project(hardware)

include_directories(${hardware_SOURCE_DIR}/include)

add_library(hardware serialdevice.cpp mcp23008.cpp debounce.cpp)