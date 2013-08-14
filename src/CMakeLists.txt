# we include this directory for config.h
include_directories(${alcyone_SOURCE_DIR}/include)

add_executable(alcyone main.cpp alcyone.cpp)

target_link_libraries(alcyone logutil hardware wiringPi boost_thread-mt boost_program_options)