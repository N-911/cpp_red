cmake_minimum_required(VERSION 3.15)
project(w1)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(w1
#        logger.cpp
        test_runner.h
        airline_ticket.h
#        sort_by.cpp
        update_field.cpp
        )
