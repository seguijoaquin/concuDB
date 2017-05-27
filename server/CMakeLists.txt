cmake_minimum_required(VERSION 3.5)
project(ConcuServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES src/main.cpp ../utils/Logger.h ../utils/Logger.cpp ../utils/Constants.h ../utils/Queue.h ../utils/Messages.h src/Server.h src/Server.cpp) 
add_executable(ConcuServer ${SOURCE_FILES})
