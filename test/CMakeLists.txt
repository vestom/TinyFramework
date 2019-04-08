cmake_minimum_required (VERSION 3.0)
project (TF_Test)

SET(GCC_LINUX_LINK_FLAGS    "-pthread")
#add_definitions(${GCC_LINUX_LINK_FLAGS})
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINUX_LINK_FLAGS}" )

include_directories(.)
include_directories(../include)

# Insert sources by wildcard
file(GLOB SOURCES "*.cpp")

# Add modules 
#add_subdirectory (modules/TinyFramework/src)
file(GLOB TF_SOURCES "../src/Platform/Linux/*.cpp")

set(SOURCES
   ${SOURCES}
   ${TF_SOURCES}
)

# Main executable
add_executable(tf_test ${SOURCES})

