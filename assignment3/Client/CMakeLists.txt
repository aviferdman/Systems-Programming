cmake_minimum_required(VERSION 3.15)
project(Client)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

link_libraries("-lboost_system")

add_executable(Client
        include/connectionHandler.h
        include/IOThread.h
        include/ServerThread.h
        src/connectionHandler.cpp
        src/echoClient.cpp
        src/IOThread.cpp
        src/ServerThread.cpp
        CMakeLists.txt
        makefile)

find_package(Boost 1.56 REQUIRED COMPONENTS
        date_time filesystem iostreams)
target_link_libraries(Client Boost::date_time Boost::filesystem
        Boost::iostreams pthread)
