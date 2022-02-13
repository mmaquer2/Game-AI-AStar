# The minimum required version of CMake to use
cmake_minimum_required(VERSION 3.10)

#Require C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Set the project name to your project name
project(App)

# Where are the include directories
include_directories("./include/")

# Check the build system and add the necessary file paths
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message("Building on a Linux system.")
    set(CMAKE_CXX_FLAGS "-pthread")
    include_directories("/usr/include/")
    link_directories("/usr/lib/x86_64-linux-gnu/")

elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message("Building on a MacOS system.")
    include_directories("/usr/local/include/")

elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    message("Building on a Windows system.")

else ()
    message("Unknown build system!")
endif()

# Set a list of project source files so it's easier to read
set (SRC_LIST
        ./src/Node.cpp
        ./src/Graph.cpp
        ./src/AStar.cpp
        ./src/main.cpp
        )

# create exccutable for main App
add_executable(App ${SRC_LIST})
