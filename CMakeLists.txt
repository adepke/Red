cmake_minimum_required(VERSION 3.0)

option(ASSERTIONS "Use compile time and runtime assertions when possible" ON)
option(FORCEDINLINES "Force all inlines" OFF)
option(VEC_DOUBLE "Vectors allocate each component as doubles, increasing accuracy" OFF)
option(PRECOMPUTED_RAY "Precompute ray components to reduce execution overhead" OFF)

set (CMAKE_CXX_STANDARD 14)

INCLUDE("Red.cmake")

ADD_LIBRARY(Red STATIC
            ${Red_SRC})

TARGET_LINK_LIBRARIES(Red
            ${Red_DEPS}
            ${Red_ADDITIONAL_DEPS}
            ${SOLUTION_STATIC_LIB_DEPS}
            ${SOLUTION_GENERAL_DEPS})

