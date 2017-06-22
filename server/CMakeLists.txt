cmake_minimum_required(VERSION 3.5)
project(ConcuServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES src/main.cpp src/Database.h src/Database.cpp ../utils/Logger.h ../utils/Lock.h ../utils/Lock.cpp ../utils/LockRead.h ../utils/LockRead.cpp  ../utils/LockWrite.h  ../utils/LockWrite.cpp ../utils/signals/EventHandler.h ../utils/signals/SENAL_SALIDA_Handler.h ../utils/signals/SignalHandler.h ../utils/signals/SignalHandler.cpp ../utils/Logger.cpp ../utils/Constants.h ../utils/Queue.h ../utils/Messages.h src/Server.h src/Server.cpp) 
add_executable(ConcuServer ${SOURCE_FILES})
