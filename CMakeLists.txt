cmake_minimum_required(VERSION 3.0)

set (CMAKE_CXX_STANDARD 14)

INCLUDE("Red.cmake")

ADD_LIBRARY(Red STATIC
            ${Red_SRC})

TARGET_LINK_LIBRARIES(Red
            ${Red_DEPS}
            ${Red_ADDITIONAL_DEPS}
            ${SOLUTION_STATIC_LIB_DEPS}
            ${SOLUTION_GENERAL_DEPS})

