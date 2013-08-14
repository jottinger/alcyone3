cmake_minimum_required(VERSION 2.7)
project(wiringPiStub)

include_directories(${wiringPiStub_SOURCE_DIR}/include)

add_library(wiringPi wiringPi.c wiringPiI2C.c wiringSerial.c)