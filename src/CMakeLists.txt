# we include this directory for config.h
include_directories(${PROJECT_SOURCE_DIR})

include_directories(${alcyone_SOURCE_DIR}/src/include)
include_directories(${hardware_SOURCE_DIR}/src/include)

add_executable(alcyone main.cpp alcyone.cpp midi.cpp pedal.cpp
	digitalinput.cpp webservice.cpp)

target_link_libraries(alcyone hardware wiringPi onioncpp_static 
	onion_handlers_static onion_static 
	boost_thread-mt boost_program_options pthread rt)