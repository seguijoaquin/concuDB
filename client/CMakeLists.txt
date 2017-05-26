cmake_minimum_required(VERSION 3.5)
project(ConcuClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES src/main.cpp ../utils/Logger.h ../utils/Logger.cpp ../utils/Queue.h ../utils/Messages.h src/Client.h src/Client.cpp) 
add_executable(ConcuClient ${SOURCE_FILES})
