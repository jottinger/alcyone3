cmake_minimum_required (VERSION 2.7)

project (alcyone)

include(misc.cmake)
include(arch.cmake)

target_architecture(CMAKE_TARGET_ARCHITECTURES)

message(STATUS "Target architectures: ${CMAKE_TARGET_ARCHITECTURES}")

set (default_verbose_value false)
set (default_host_port 8090)
set (default_flare_time 600)
set (min_flare_time 100)
set (max_flare_time 2000)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${hardware_SOURCE_DIR}/include")
include_directories("${log_SOURCE_DIR}/include")

is_symbol_defined(symdef __x86_64__)
if(symdef) 
	message(STATUS "Using wiringPiStub for non-ARMv6 Architecture")
	add_subdirectory(wiringPiStub)
	include_directories(${wiringPiStub_SOURCE_DIR}/include)
	link_directories(${wiringPiStub_BINARY_DIR})	
endif()

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-Wall -O2 -pedantic")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_subdirectory(log)
add_subdirectory(hardware)
add_subdirectory(src)
