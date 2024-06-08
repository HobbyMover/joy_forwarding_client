cmake_minimum_required(VERSION 3.0)
project(joy_fowarding_client)

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when CMake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`
file(GLOB_RECURSE sources main.cpp input_processing/*.cpp joy_client/*.cpp)
message(sources="${sources}")



# you can use set(sources src/main.cpp) etc if you don't want to
# use globbing to find files automatically

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
add_executable(target ${sources})
target_include_directories(target PUBLIC input_processing joy_client)

# just for example add some compiler flags
#target_compile_options(target PUBLIC -std=c++14 -Wall -Wfloat-conversion)
