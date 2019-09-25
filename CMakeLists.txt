
cmake_minimum_required(VERSION 3.13.1)

#include_directories(AFTER ./include)

if(NOT TF_TARGET)
   message(STATUS "TinyFramework: application target not defined")
endif(NOT TF_TARGET)

target_include_directories(${TF_TARGET} PRIVATE include)

target_sources(${TF_TARGET} PRIVATE
    src/OSAL/FreeRTOS/Event.cpp
    src/OSAL/FreeRTOS/Mutex.cpp
    src/OSAL/FreeRTOS/Thread.cpp
    src/OSAL/FreeRTOS/Timer.cpp
    src/OSAL/Linux/Event.cpp
    src/OSAL/Linux/Mutex.cpp
    src/OSAL/Linux/Serial.cpp
    src/OSAL/Linux/Thread.cpp
    src/OSAL/Linux/Timer.cpp
    src/OSAL/Generic/Log.cpp
    src/OSAL/Generic/MsgQueue.cpp
    src/OSAL/Zephyr/Event.cpp
    src/OSAL/Zephyr/Mutex.cpp
    src/OSAL/Zephyr/Serial.cpp
    src/OSAL/Zephyr/Thread.cpp
    src/OSAL/Zephyr/Timer.cpp
)
