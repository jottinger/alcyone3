# we include this directory for config.h
include_directories(${PROJECT_SOURCE_DIR})

include_directories(${alcyone_SOURCE_DIR}/src/include)

add_executable(alcyone main.cpp alcyone.cpp midi.cpp pedal.cpp)

target_link_libraries(alcyone logutil hardware wiringPi boost_thread-mt boost_program_options)