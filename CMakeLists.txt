cmake_minimum_required(VERSION 3.10)

# Define the ACME project!
project(ACME VERSION 1.00 DESCRIPTION "Age of Control: Machine Expanse")

# Define a target named `loot_customization` that will control all the commands
# for building the plugin that Chris(tina) writes.
add_library(loot_customization SHARED plugin/loot_customization.c)
# By default, we configure the build system so that all the symbols
# generated during compilation of the plugin are hidden. That means that 
# nefarious ACME players won't be able to call functions other than the
# ones that Chris(tina) deems acceptable.
set_property(TARGET loot_customization PROPERTY C_VISIBILITY_PRESET hidden)

# Define a target named `acme` that will control all the commands for
# building the game itself.
add_executable(acme acme/acme.c)
# We have to link the game with the `dl` library in order to be able to
# use the operating system's dynamic library loading system at runtime.
target_link_libraries(acme dl)

# Configure a preprocessor variable that specifies where Chris(tina)'s
# library resides in the filesystem.
set(PLUGIN_DIR ${CMAKE_BINARY_DIR})
add_compile_definitions(PLUGIN_DIR="${PLUGIN_DIR}")