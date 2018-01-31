#
# This file was genared by proj2cmake and will be overwritten on it's next run!
# Please put all configurations in the cmake_conf/*.cmake files.
#

cmake_minimum_required(VERSION 2.8)


INCLUDE("Red.cmake")

ADD_LIBRARY(Red STATIC
            ${Red_SRC})

TARGET_LINK_LIBRARIES(Red
            ${Red_DEPS}
            ${Red_ADDITIONAL_DEPS}
            ${SOLUTION_STATIC_LIB_DEPS}
            ${SOLUTION_GENERAL_DEPS})

