cmake_minimum_required(VERSION 3.10)

project(dynamic_loading_demo VERSION 1.00 DESCRIPTION "A demo of how to do dynamic library loading in Linux")

add_library(plugin SHARED library/plugin.c)
set_property(TARGET plugin PROPERTY C_VISIBILITY_PRESET hidden)

add_executable(application application/application.c)
target_link_libraries(application dl)