cmake_minimum_required(VERSION 2.7)
project(logutil)

include_directories(${logutil_SOURCE_DIR}/include)

add_library(logutil log.cpp)
