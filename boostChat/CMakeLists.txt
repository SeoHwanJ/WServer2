cmake_minimum_required(VERSION 3.26)
project(boostChat)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT /opt/homebrew/Cellar/boost/1.82.0_1)
set(BOOST_INCLUDEDIR /opt/homebrew/Cellar/boost/1.82.0_1/include)
set(BOOST_LIBRARY_DIR /opt/homebrew/Cellar/boost/1.82.0_1/lib)

find_package(Boost COMPONENTS system filesystem REQUIRED)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif ()
include_directories(${Boost_INCLUDE_DIR})
add_executable(boostChat main.cpp
        Session.cpp
        Server.cpp)
#프로그램 최소 버전


